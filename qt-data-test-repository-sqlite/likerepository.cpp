#include <QSqlQuery>
#include <QSqlError>

#include "likerepository.h"

using namespace QtDataTest::Repository::Sqlite;

LikeRepository::LikeRepository(QString dbName) {
    this->dbName = dbName;

    checkLikeTable();
}

void LikeRepository::createLike(int userId, int postId) {
    auto db = QSqlDatabase::database(dbName);

    QSqlQuery query(db);

    query.prepare(R"(
        insert into likes(user_id, post_id)
        values (:user_id, :post_id);
    )");

    query.bindValue(":user_id", userId);
    query.bindValue(":post_id", postId);

    if (!query.exec()) {
        qDebug() << "Error inserting data: " << query.lastError().text();
    }
}

void LikeRepository::deleteLike(int userId, int postId) {
    auto db = QSqlDatabase::database(dbName);

    QSqlQuery query(db);

    query.prepare(R"(
        delete from
            likes
        where
            user_id = :user_id
            and post_id = :post_id;
    )");

    query.bindValue(":user_id", userId);
    query.bindValue(":post_id", postId);

    if (!query.exec()) {
        qDebug() << "Error deleting data: " << query.lastError().text();
    }
}

void LikeRepository::checkLikeTable() {
    auto db = QSqlDatabase::database(dbName);

    QSqlQuery query(db);

    auto createTableQuery = R"(
        create table if not exists likes (
            id integer primary key autoincrement,
            user_id integer not null,
            post_id integer not null,
            unique(user_id, post_id),
            foreign key (user_id) references users(id) on delete cascade on update cascade,
            foreign key (post_id) references posts(id) on delete cascade on update cascade
        )
    )";

    if (!query.exec(createTableQuery)) {
        qDebug() << "Create table failed: " << query.lastError().text();
    }
}
