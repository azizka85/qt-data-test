QT += core sql

TARGET = QtDataTest.Repository.Sqlite

TEMPLATE = lib
DEFINES += QT_DATA_TEST_REPOSITORY_SQLITE_LIBRARY

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    likerepository.cpp \
    postrepository.cpp \
    sessionrepository.cpp \
    userrepository.cpp

HEADERS += \
    likerepository.h \
    postrepository.h \
    qt-data-test-repository-sqlite_global.h \
    sessionrepository.h \
    userrepository.h

INCLUDEPATH += \
    ../

DESTDIR = $$PWD/../lib

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
