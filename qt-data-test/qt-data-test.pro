QT += testlib sql
QT -= gui

CONFIG += c++20 qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_userrepositorytest.cpp

INCLUDEPATH += \
        ../

LIBS += -L$$PWD/../lib -lQtDataTest.Repository.Sqlite
