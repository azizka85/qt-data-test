#ifndef POSTREPOSITORY_H
#define POSTREPOSITORY_H

#include <QSqlQuery>

#include <ipostrepository.h>

#include <qt-data-test-repository-sqlite_global.h>

using namespace QtDataTest::Prototype;

namespace QtDataTest::Repository::Sqlite {
class QT_DATA_TEST_REPOSITORY_SQLITE_EXPORT PostRepository : public IPostRepository
{
public:
    explicit PostRepository(QString dbName);

    std::optional<int> create(std::optional<int> userId, Data::Post &post);

    std::optional<Data::Post> get(int id, std::optional<int> userId);

    QList<Data::Post> list(std::optional<int> userId);

    QList<Data::Post> likedList(std::optional<int> userId);

    void checkPostTable();

    Data::Post read(QSqlQuery& query);

private:
    QString dbName;
};
}

#endif // POSTREPOSITORY_H
