#include <QCryptographicHash>

#include <QSqlQuery>
#include <QSqlError>

#include "userrepository.h"

using namespace QtDataTest::Repository::Sqlite;

UserRepository::UserRepository(QString dbName) {
    this->dbName = dbName;

    checkUserTable();
    checkSettingsTable();
}

std::optional<int> UserRepository::create(Data::User &user) {
    auto db = QSqlDatabase::database(dbName);

    if (!db.transaction()) {
        qDebug() << "Failed to start transaction:" << db.lastError().text();

        return std::nullopt;
    }

    auto id = createWT(user);

    if (!db.commit()) {
        qDebug() << "Commit failed:" << db.lastError().text();

        db.rollback();
    }

    return id;
}

std::optional<int> UserRepository::getId(QString &email, QString &password) {
    auto passwordHash = QCryptographicHash::hash(
        password.toUtf8(),
        QCryptographicHash::Md5
    ).toHex();

    auto db = QSqlDatabase::database(dbName);

    QSqlQuery query(db);

    query.prepare(R"(
        select
            id
        from
            users
        where
            email = :email
            and password = :password
    )");

    query.bindValue(":email", email);
    query.bindValue(":password", passwordHash);

    if (query.exec()) {
        if (query.next()) {
            return query.value("id").toInt();
        }
    } else {
        qDebug() << "Error fetching data: " << query.lastError().text();
    }

    return std::nullopt;
}

std::optional<Data::User> UserRepository::getUser(int id) {
    auto db = QSqlDatabase::database(dbName);

    QSqlQuery query(db);

    query.prepare(R"(
        select
            u.id user_id, u.first_name, u.last_name,
            case
                when s.display_email = false then null
                else u.email
            end email,
            s.id settings_id, s.posts_per_page, s.display_email
        from
            users u, settings s
        where
            s.user_id = u.id
            and u.id = :id
    )");

    query.bindValue(":id", id);

    if (query.exec()) {
        if (query.next()) {
            return read(query);
        }
    } else {
        qDebug() << "Error fetching data: " << query.lastError().text();
    }

    return std::nullopt;
}

bool UserRepository::edit(Data::Settings &settings) {
    auto db = QSqlDatabase::database(dbName);

    QSqlQuery query(db);

    query.prepare(R"(
        update
            settings
        set
            posts_per_page = :posts_per_page,
            display_email = :display_email
        where
            user_id = :user_id;
    )");

    query.bindValue(":posts_per_page", settings.postsPerPage);
    query.bindValue(":display_email", settings.displayEmail);
    query.bindValue(":user_id", settings.userId);

    if (!query.exec()) {
        qDebug() << "Error updating data: " << query.lastError().text();

        return false;
    }

    return true;
}

std::optional<int> UserRepository::createWT(Data::User &user) {
    auto id = createUserWT(user);

    if (id.has_value()) {
        user.id = id.value();
        user.settings.userId = id.value();
    }

    auto settingsId = createSettingsWT(user.settings);

    if (settingsId.has_value()) {
        user.settings.id = settingsId.value();
    }

    return id;
}

std::optional<int> UserRepository::createUserWT(Data::User &user) {
    QVariant password;

    if (user.password.has_value())
        password = QCryptographicHash::hash(
            user.password.value().toUtf8(),
            QCryptographicHash::Md5
        ).toHex();

    auto db = QSqlDatabase::database(dbName);

    QSqlQuery query(db);

    query.prepare("\
        insert into users(first_name, last_name, email, password) \
        values (:first_name, :last_name, :email, :password) \
    ");

    query.bindValue(":first_name", user.firstName);
    query.bindValue(":last_name", user.lastName);
    query.bindValue(":email", user.email.has_value()
        ? QVariant(user.email.value())
        : QVariant()
    );
    query.bindValue(":password", password);

    if (!query.exec()) {
        qDebug() << "Error inserting data: " << query.lastError().text();

        return std::nullopt;
    }

    return query.lastInsertId().toInt();
}

std::optional<int> UserRepository::createSettingsWT(Data::Settings &settings) {
    auto db = QSqlDatabase::database(dbName);

    QSqlQuery query(db);

    query.prepare("\
        insert into settings(user_id, posts_per_page, display_email) \
        values (:user_id, :posts_per_page, :display_email) \
    ");

    query.bindValue(":user_id", settings.userId);
    query.bindValue(":posts_per_page", settings.postsPerPage);
    query.bindValue(":display_email", settings.displayEmail);

    if (!query.exec()) {
        qDebug() << "Error inserting data: " << query.lastError().text();

        return std::nullopt;
    }

    return query.lastInsertId().toInt();
}

void UserRepository::checkUserTable() {
    auto db = QSqlDatabase::database(dbName);

    QSqlQuery query(db);

    auto createTableQuery = R"(
        create table if not exists users (
            id integer primary key autoincrement,
            first_name text not null,
            last_name text not null,
            email text not null unique,
            password text not null
        )
    )";

    if (!query.exec(createTableQuery)) {
        qDebug() << "Create table failed: " << query.lastError().text();
    }
}

void UserRepository::checkSettingsTable() {
    auto db = QSqlDatabase::database(dbName);

    QSqlQuery query(db);

    auto createTableQuery = R"(
        create table if not exists settings (
            id integer primary key autoincrement,
            user_id integer not null,
            posts_per_page integer not null default 10,
            display_email boolean not null default 1,
            foreign key (user_id) references users(id) on delete cascade on update cascade
        )
    )";

    if (!query.exec(createTableQuery)) {
        qDebug() << "Create table failed: " << query.lastError().text();
    }
}

Data::User UserRepository::read(QSqlQuery &query) {
    return Data::User {
        .id = query.value("user_id").toInt(),
        .firstName = query.value("first_name").toString(),
        .lastName = query.value("last_name").toString(),
        .email = query.value("email").toString(),
        .settings = Data::Settings {
            .id = query.value("settings_id").toInt(),
            .userId = query.value("user_id").toInt(),
            .postsPerPage = query.value("posts_per_page").toInt(),
            .displayEmail = query.value("display_email").toBool()
        }
    };
}
