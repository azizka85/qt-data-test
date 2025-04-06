#ifndef QT_DATA_TEST_REPOSITORY_SQLITE_USERREPOSITORY_H
#define QT_DATA_TEST_REPOSITORY_SQLITE_USERREPOSITORY_H

#include <QSqlQuery>

#include <qt-data-test-prototype/iuserrepository.h>

#include "qt-data-test-repository-sqlite_global.h"

using namespace QtDataTest::Prototype;

namespace QtDataTest::Repository::Sqlite {
class QT_DATA_TEST_REPOSITORY_SQLITE_EXPORT UserRepository: public IUserRepository
{
public:
    explicit UserRepository(QString dbName);

    std::optional<int> create(Data::User &user);

    std::optional<int> getId(QString &email, QString &password);

    std::optional<Data::User> getUser(int id);

    bool edit(Data::Settings &settings);

    std::optional<int> createWT(Data::User &user);

    std::optional<int> createUserWT(Data::User &user);

    std::optional<int> createSettingsWT(Data::Settings &settings);

    void checkUserTable();

    void checkSettingsTable();

    Data::User read(QSqlQuery& query);    

private:
    QString dbName;
};
}

#endif // USERREPOSITORY_H
