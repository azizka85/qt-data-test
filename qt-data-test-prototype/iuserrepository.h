#ifndef IUSERREPOSITORY_H
#define IUSERREPOSITORY_H

#include <QString>

#include <optional>

#include <data/user.h>

namespace QtDataTest::Prototype {
class IUserRepository {
    virtual std::optional<int> create(Data::User &user) = 0;

    virtual std::optional<int> getId(QString &email, QString &password) = 0;

    virtual std::optional<Data::User> getUser(int id) = 0;

    virtual bool edit(Data::Settings &settings) = 0;
};
}

#endif // IUSERREPOSITORY_H
