#include <QSqlError>

#include "postrepository.h"

using namespace QtDataTest::Repository::Sqlite;

PostRepository::PostRepository(QString dbName) {
    this->dbName = dbName;

    checkPostTable();
}

std::optional<int> PostRepository::create(std::optional<int> userId, Data::Post &post) {
    auto db = QSqlDatabase::database(dbName);

    QSqlQuery query(db);

    query.prepare(R"(
        insert into posts(user_id, title, text, abstract)
        values (:user_id, :title, :text, :abstract)
    )");

    query.bindValue(":user_id", userId.has_value()
        ? QVariant(userId.value())
        : QVariant()
    );

    query.bindValue(":title", post.title);
    query.bindValue(":text", post.text);
    query.bindValue(":abstract", post.abstract);

    if (!query.exec()) {
        qDebug() << "Error inserting data: " << query.lastError().text();

        return std::nullopt;
    }

    return query.lastInsertId().toInt();
}

std::optional<Data::Post> PostRepository::get(int id, std::optional<int> userId) {
    auto db = QSqlDatabase::database(dbName);

    QSqlQuery query(db);

    query.prepare(R"(
        select
            u.id user_id, u.first_name, u.last_name,
            case
                when s.display_email is null or s.display_email = false then null
                else u.email
            end email,
            p.id post_id, p.title, p.text, p.abstract,
            case
                when l.id is null then false
                else true
            end liked
        from
            posts p
        left join
            users u
            on p.user_id = u.id
        left join
            settings s
            on p.user_id = s.user_id
        left join
            likes l
            on p.id = l.post_id
                and l.user_id = :user_id
        where
          p.id = :id;
    )");

    query.bindValue(":id", id);

    query.bindValue(":user_id", userId.has_value()
        ? QVariant(userId.value())
        : QVariant()
    );

    if (query.exec()) {
        if (query.next()) {
            return read(query);
        }
    } else {
        qDebug() << "Error fetching data: " << query.lastError().text();
    }

    return std::nullopt;
}

QList<Data::Post> PostRepository::list(std::optional<int> userId) {
    auto db = QSqlDatabase::database(dbName);

    QSqlQuery query(db);

    query.prepare(R"(
        select
            u.id user_id, u.first_name, u.last_name,
            case
                when s.display_email is null or s.display_email = false then null
                else u.email
            end email,
            p.id post_id, p.title, p.text, p.abstract,
            case
                when l.id is null then false
                else true
            end liked
        from
            posts p
        left join
            users u
            on p.user_id = u.id
        left join
            settings s
            on p.user_id = s.user_id
        left join
            likes l
            on p.id = l.post_id
                and l.user_id = :user_id;
    )");

    query.bindValue(":user_id", userId.has_value()
        ? QVariant(userId.value())
        : QVariant()
    );

    QList<Data::Post> list;

    if (query.exec()) {
        while (query.next()) {
            list.append(
                read(query)
            );
        }
    } else {
        qDebug() << "Error fetching data: " << query.lastError().text();
    }

    return list;
}

QList<Data::Post> PostRepository::likedList(std::optional<int> userId) {
    auto db = QSqlDatabase::database(dbName);

    QSqlQuery query(db);

    query.prepare(R"(
        select
            u.id user_id, u.first_name, u.last_name,
            case
                when s.display_email is null or s.display_email = false then null
                else u.email
            end email,
            p.id post_id, p.title, p.text, p.abstract,
            case
                when l.id is null then false
                else true
            end liked
        from
            posts p
        left join
            users u
            on p.user_id = u.id
        left join
            settings s
            on p.user_id = s.user_id
        inner join
            likes l
            on p.id = l.post_id
                and l.user_id = :user_id;
    )");

    query.bindValue(":user_id", userId.has_value()
        ? QVariant(userId.value())
        : QVariant()
    );

    QList<Data::Post> list;

    if (query.exec()) {
        while (query.next()) {
            list.append(
                read(query)
            );
        }
    } else {
        qDebug() << "Error fetching data: " << query.lastError().text();
    }

    return list;
}

void PostRepository::checkPostTable() {
    auto db = QSqlDatabase::database(dbName);

    QSqlQuery query(db);

    auto createTableQuery = R"(
        create table if not exists posts (
            id integer primary key autoincrement,
            user_id integer null,
            title text not null,
            text text null,
            abstract text null,
            foreign key (user_id) references users(id) on delete cascade on update cascade
        )
    )";

    if (!query.exec(createTableQuery)) {
        qDebug() << "Create table failed: " << query.lastError().text();
    }
}

Data::Post PostRepository::read(QSqlQuery &query) {
    Data::Post post {
        .id = query.value("post_id").toInt(),
        .title = query.value("title").toString(),
        .text = query.value("text").toString(),
        .abstract = query.value("abstract").toString(),
        .liked = query.value("liked").toBool()
    };

    if (!query.value("user_id").isNull()) {
        Data::User user {
            .id = query.value("user_id").toInt(),
            .firstName = query.value("first_name").toString(),
            .lastName = query.value("last_name").toString()
        };

        if (!query.value("email").isNull()) {
            user.email = query.value("email").toString();
        }

        post.author = user;
    }

    return post;
}

