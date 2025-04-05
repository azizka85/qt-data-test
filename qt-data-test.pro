TEMPLATE = subdirs

SUBDIRS += \
    qt-data-test \
    qt-data-test-console \
    qt-data-test-repository-sqlite \
    qt-data-test-prototype

qt-data-test-console.depends = qt-data-test-repository-sqlite
