QT += core network

TARGET = QtDataTest.Repository.RestAPI

TEMPLATE = lib
DEFINES += QT_DATA_TEST_REPOSITORY_REST_API_LIBRARY

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    sessionrepository.cpp \
    userrepository.cpp \
    utils.cpp

HEADERS += \
    qt-data-test-repository-rest-api_global.h \
    sessionrepository.h \
    userrepository.h \
    utils.h

INCLUDEPATH += \
    ../

DESTDIR = $$PWD/../lib

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
