#include <QSqlQuery>
#include <QSqlError>

#include "sessionrepository.h"

using namespace QtDataTest::Repository::Sqlite;

SessionRepository::SessionRepository(UserRepository* userRepository, QString dbName) {
    this->dbName = dbName;
    this->userRepository = userRepository;

    checkSessionTable();
}

std::optional<int> SessionRepository::create(int userId, QString &code) {
    auto db = QSqlDatabase::database(dbName);

    QSqlQuery query(db);

    query.prepare(R"(
        insert into sessions(user_id, code)
        values (:user_id, :code)
    )");

    query.bindValue(":user_id", userId);
    query.bindValue(":code", code);

    if (!query.exec()) {
        qDebug() << "Error inserting data: " << query.lastError().text();

        return std::nullopt;
    }

    return query.lastInsertId().toInt();
}

std::optional<Data::User> SessionRepository::getUser(int sessionId) {
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
            users u, settings s, sessions t
        where
            s.user_id = u.id
            and u.id = t.user_id
            and t.id = :id;
    )");

    query.bindValue(":id", sessionId);

    if (query.exec()) {
        if (userRepository == nullptr) {
            qDebug() << "UserRepository wasn't created";
        } else if (query.next()) {
            return userRepository->read(query);
        }
    } else {
        qDebug() << "Error fetching data: " << query.lastError().text();
    }

    return std::nullopt;
}

std::optional<int> SessionRepository::getIdByCode(QString &sessionCode) {
    auto db = QSqlDatabase::database(dbName);

    QSqlQuery query(db);

    query.prepare(R"(
        select
            id
        from
            sessions
        where
            code = :code;
    )");

    query.bindValue(":code", sessionCode);

    if (query.exec()) {
        if (query.next()) {
            return query.value("id").toInt();
        }
    } else {
        qDebug() << "Error fetching data: " << query.lastError().text();
    }

    return std::nullopt;
}

void SessionRepository::checkSessionTable() {
    auto db = QSqlDatabase::database(dbName);

    QSqlQuery query(db);

    auto createTableQuery = R"(
        create table if not exists sessions (
            id integer primary key autoincrement,
            user_id integer not null,
            code text not null,
            foreign key (user_id) references users(id) on delete cascade on update cascade
        )
    )";

    if (!query.exec(createTableQuery)) {
        qDebug() << "Create table failed: " << query.lastError().text();
    }
}
