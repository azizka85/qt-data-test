#ifndef QT_DATA_TEST_REPOSITORY_SQLITE_SESSIONREPOSITORY_H
#define QT_DATA_TEST_REPOSITORY_SQLITE_SESSIONREPOSITORY_H

#include <qt-data-test-prototype/isessionrepository.h>

#include "userrepository.h"

#include "qt-data-test-repository-sqlite_global.h"

using namespace QtDataTest::Prototype;

namespace QtDataTest::Repository::Sqlite {
class QT_DATA_TEST_REPOSITORY_SQLITE_EXPORT SessionRepository : public ISessionRepository
{
public:
    explicit SessionRepository(UserRepository* userRepository, QString dbName);

    std::optional<int> create(int userId, QString &code);

    std::optional<Data::User> getUser(int sessionId);

    std::optional<int> getIdByCode(QString &sessionCode);

    void checkSessionTable();

private:
    QString dbName;
    UserRepository* userRepository;
};
}

#endif // SESSIONREPOSITORY_H
