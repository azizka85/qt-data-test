#ifndef ISESSIONREPOSITORY_H
#define ISESSIONREPOSITORY_H

#include <optional>

#include "data/user.h"

namespace QtDataTest::Prototype {
class ISessionRepository {
    virtual std::optional<int> create(int userId, QString &code) = 0;

    virtual std::optional<Data::User> getUser(int sessionId) = 0;

    virtual std::optional<int> getIdByCode(QString &sessionCode) = 0;
};
}

#endif // ISESSIONREPOSITORY_H
