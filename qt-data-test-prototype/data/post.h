#ifndef POST_H
#define POST_H

#include <QString>

#include <optional>

#include "data/user.h"

namespace QtDataTest::Prototype::Data {
struct Post {
    int id;
    QString title;
    QString text;
    QString abstract;
    bool liked;

    std::optional<User> author;
};
}

#endif // POST_H
