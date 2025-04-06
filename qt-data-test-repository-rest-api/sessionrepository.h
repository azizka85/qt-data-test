#ifndef QT_DATA_TEST_REPOSITORY_REST_API_SESSIONREPOSITORY_H
#define QT_DATA_TEST_REPOSITORY_REST_API_SESSIONREPOSITORY_H

#include <QObject>

#include <QNetworkAccessManager>

#include <qt-data-test-prototype/isessionrepository.h>

#include "userrepository.h"

using namespace QtDataTest::Prototype;

namespace QtDataTest::Repository::RestAPI {
class QT_DATA_TEST_REPOSITORY_REST_API_EXPORT SessionRepository : public QObject, ISessionRepository
{
    Q_OBJECT

public:
    explicit SessionRepository(QString baseUrl, UserRepository *userRepository, QObject *parent = nullptr);

    std::optional<int> create(int userId, QString &code);

    std::optional<Data::User> getUser(int sessionId);

    std::optional<int> getIdByCode(QString &sessionCode);

private:
    QString baseUrl;
    QNetworkAccessManager *manager;
    UserRepository *userRepository;
};
}

#endif // SESSIONREPOSITORY_H
