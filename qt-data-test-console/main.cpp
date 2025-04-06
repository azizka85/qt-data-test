#include <QCoreApplication>

#include <QSqlError>

#include <QUrl>

#include <QJsonArray>

#include <qt-data-test-repository-sqlite/userrepository.h>
#include <qt-data-test-repository-sqlite/sessionrepository.h>
#include <qt-data-test-repository-sqlite/postrepository.h>
#include <qt-data-test-repository-sqlite/likerepository.h>

#include <qt-data-test-repository-rest-api/userrepository.h>
#include <qt-data-test-repository-rest-api/sessionrepository.h>

using namespace QtDataTest::Repository;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString dbName = "qt-data-test";

    auto db = QSqlDatabase::addDatabase("QSQLITE", dbName);

    db.setDatabaseName("example.db");

    if (!db.open()) {
        qDebug() << "Error: Unable to open database: " << db.lastError().text();
    } else {
        Sqlite::UserRepository userRepository(dbName);

        auto user = Data::User {
            .firstName = "Test",
            .lastName = "Test",
            .email = "test@test.test",
            .password = "test",
            .settings = Data::Settings {
                .postsPerPage = 12,
                .displayEmail = true
            }
        };

        userRepository.create(user);

        auto userInstance = userRepository.getUser(1);

        QString email = "test@test.test";
        QString password = "test";

        auto userId = userRepository.getId(email, password);

        auto userSettings = Data::Settings {
            .userId = userId.value(),
            .postsPerPage = 34,
            .displayEmail = false
        };

        userRepository.edit(userSettings);

        userInstance = userRepository.getUser(1);

        Sqlite::SessionRepository sessionRepository(&userRepository, dbName);

        QString sessionCode = "wewewe";

        auto sessionId = sessionRepository.create(1, sessionCode);

        userInstance = sessionRepository.getUser(sessionId.value());

        sessionId = sessionRepository.getIdByCode(sessionCode);

        Sqlite::PostRepository postRepository(dbName);

        auto post = Data::Post {
            .title = "Title",
            .text = "Text",
            .abstract = "Abstract"\
        };

        auto postId = postRepository.create(1, post);

        auto postInstance = postRepository.get(1, 1);

        auto postsList = postRepository.list(1);

        auto likedPostsList = postRepository.likedList(1);

        Sqlite::LikeRepository likeRepository(dbName);

        likeRepository.createLike(1, 1);

        likedPostsList = postRepository.likedList(1);

        likeRepository.deleteLike(1, 1);

        likedPostsList = postRepository.likedList(1);
    }

    QString baseUrl = "https://fastapi-posts.onrender.com";

    RestAPI::UserRepository userRepository(baseUrl);
    RestAPI::SessionRepository sessionRepository(baseUrl, &userRepository);

    QString email = "test@test.test";
    QString password = "test";

    auto user = Data::User {
        .firstName = "Test",
        .lastName = "Test",
        .email = email,
        .password = password
    };

    auto id = userRepository.create(user);

    id = userRepository.getId(email, password);

    QString sessionCode = "f8fd11de-124c-11f0-8648-7a1a7a228db8";

    id = sessionRepository.getIdByCode(sessionCode);

    return a.exec();
}
