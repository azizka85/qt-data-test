#include <QCoreApplication>
#include <QtTest>

#include <QSqlError>

#include <qt-data-test-repository-sqlite/userrepository.h>

using namespace QtDataTest::Repository::Sqlite;

class UserRepositoryTest : public QObject
{
    Q_OBJECT

public:
    UserRepositoryTest();
    ~UserRepositoryTest();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testSqlite();

private:
    QString dbName;
};

UserRepositoryTest::UserRepositoryTest() {}

UserRepositoryTest::~UserRepositoryTest() {}

void UserRepositoryTest::initTestCase() {
    dbName = "qt-data-test";

    auto db = QSqlDatabase::addDatabase("QSQLITE", dbName);

    db.setDatabaseName("example.db");

    QVERIFY(db.open());
}

void UserRepositoryTest::cleanupTestCase() {
    auto db = QSqlDatabase::database(dbName);

    db.close();
}

void UserRepositoryTest::testSqlite() {
    auto db = QSqlDatabase::database(dbName);

    UserRepository userRepository(dbName);

    QVERIFY(db.transaction());

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

    auto userId = userRepository.createWT(user);

    QVERIFY(userId != std::nullopt);

    db.rollback();

    auto userInstance = userRepository.getUser(userId.value());

    QVERIFY(userInstance == std::nullopt);
}

QTEST_MAIN(UserRepositoryTest)

#include "tst_userrepositorytest.moc"
