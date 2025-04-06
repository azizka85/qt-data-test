#ifndef QT_DATA_TEST_REPOSITORY_REST_API_USERREPOSITORY_H
#define QT_DATA_TEST_REPOSITORY_REST_API_USERREPOSITORY_H

#include <QObject>

#include <QJsonObject>

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

#include <qt-data-test-prototype/iuserrepository.h>

#include "qt-data-test-repository-rest-api_global.h"

using namespace QtDataTest::Prototype;

namespace QtDataTest::Repository::RestAPI {
class QT_DATA_TEST_REPOSITORY_REST_API_EXPORT UserRepository: public QObject, IUserRepository
{
    Q_OBJECT

public:
    UserRepository(QString baseUrl);

    std::optional<int> create(Data::User &user);

    std::optional<int> getId(QString &email, QString &password);

    std::optional<Data::User> getUser(int id);

    bool edit(Data::Settings &settings);

    QJsonObject toJSON(Data::User& user);

    Data::User fromJSON(QJsonObject& obj);

private:
    QNetworkAccessManager *manager;

    QString baseUrl;
};
}

#endif // USERREPOSITORY_H
