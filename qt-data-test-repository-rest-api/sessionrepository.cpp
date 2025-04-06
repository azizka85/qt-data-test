#include "sessionrepository.h"

#include "utils.h"

using namespace QtDataTest::Repository::RestAPI;

SessionRepository::SessionRepository(QString baseUrl, UserRepository *userRepository, QObject *parent)
    : QObject{parent}
{
    this->baseUrl = baseUrl;

    manager = new QNetworkAccessManager(this);

    this->userRepository = userRepository;
}

std::optional<int> SessionRepository::create(int userId, QString &code) {
    return std::nullopt;
}

std::optional<Data::User> SessionRepository::getUser(int sessionId) {
    return std::nullopt;
}

std::optional<int> SessionRepository::getIdByCode(QString &sessionCode) {
    QUrl url(baseUrl + "/user");

    QNetworkRequest request(url);

    request.setRawHeader("session-code", sessionCode.toUtf8());

    auto reply = manager->get(request);

    auto doc = read(reply);

    reply->deleteLater();

    if (doc.isObject()) {
        auto obj = doc.object();

        return userRepository->fromJSON(obj).id;
    }

    return std::nullopt;
}
