#ifndef QT_DATA_TEST_REPOSITORY_REST_API_GLOBAL_H
#define QT_DATA_TEST_REPOSITORY_REST_API_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QT_DATA_TEST_REPOSITORY_REST_API_LIBRARY)
#define QT_DATA_TEST_REPOSITORY_REST_API_EXPORT Q_DECL_EXPORT
#else
#define QT_DATA_TEST_REPOSITORY_REST_API_EXPORT Q_DECL_IMPORT
#endif

#endif // QT_DATA_TEST_REPOSITORY_REST_API_GLOBAL_H
