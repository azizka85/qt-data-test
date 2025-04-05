#ifndef LIKEREPOSITORY_H
#define LIKEREPOSITORY_H

#include <QString>

#include <ilikerepository.h>

#include <qt-data-test-repository-sqlite_global.h>

using namespace QtDataTest::Prototype;

namespace QtDataTest::Repository::Sqlite {
class QT_DATA_TEST_REPOSITORY_SQLITE_EXPORT LikeRepository : public ILikeRepository
{
public:
    explicit LikeRepository(QString dbName);

    void createLike(int userId, int postId);

    void deleteLike(int userId, int postId);

    void checkLikeTable();

private:
    QString dbName;
};
}

#endif // LIKEREPOSITORY_H
