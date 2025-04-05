QT += testlib sql
QT -= gui

CONFIG += c++20 qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_userrepositorytest.cpp

INCLUDEPATH += \
        ../qt-data-test-prototype \
        ../qt-data-test-repository-sqlite

LIBS += -L$$PWD/../lib -lQtDataTest.Repository.Sqlite
