#ifndef IPOSTREPOSITORY_H
#define IPOSTREPOSITORY_H

#include <optional>

#include "data/post.h"

namespace QtDataTest::Prototype {
class IPostRepository {
    virtual std::optional<int> create(std::optional<int> userId, Data::Post &post) = 0;

    virtual std::optional<Data::Post> get(int id, std::optional<int> userId) = 0;

    virtual QList<Data::Post> list(std::optional<int> userId) = 0;

    virtual QList<Data::Post> likedList(std::optional<int> userId) = 0;
};
}

#endif // IPOSTREPOSITORY_H
