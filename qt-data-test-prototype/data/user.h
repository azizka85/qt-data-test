#ifndef USER_H
#define USER_H

#include <QString>

#include <optional>

#include <data/settings.h>

namespace QtDataTest::Prototype::Data {
struct User {
    int id;
    QString firstName;
    QString lastName;
    std::optional<QString> email;
    std::optional<QString> password;

    Settings settings;
};
}

#endif // USER_H
