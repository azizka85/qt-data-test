TEMPLATE = subdirs

SUBDIRS += \
    qt-data-test \
    qt-data-test-console \
    qt-data-test-repository-rest-api \
    qt-data-test-repository-sqlite \
    qt-data-test-prototype

qt-data-test-console.depends = qt-data-test-repository-sqlite
qt-data-test-console.depends = qt-data-test-repository-rest-api

qt-data-test.depends = qt-data-test-repository-sqlite
qt-data-test.depends = qt-data-test-repository-rest-api
