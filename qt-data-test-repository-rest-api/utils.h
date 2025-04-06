#ifndef UTILS_H
#define UTILS_H

#include <QNetworkReply>

#include <QJsonDocument>

QJsonDocument read(QNetworkReply* reply);

#endif // UTILS_H
