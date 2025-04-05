#ifndef ILIKEREPOSITORY_H
#define ILIKEREPOSITORY_H

namespace QtDataTest::Prototype {
class ILikeRepository {
    virtual void createLike(int userId, int postId) = 0;

    virtual void deleteLike(int userId, int postId) = 0;
};
}

#endif // ILIKEREPOSITORY_H
