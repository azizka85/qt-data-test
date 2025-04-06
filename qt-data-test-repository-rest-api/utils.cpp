#include <QEventLoop>

#include "utils.h"

QJsonDocument read(QNetworkReply* reply) {
    QEventLoop loop;

    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);

    loop.exec();

    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Error:" << reply->errorString();        

        return QJsonDocument();
    }

    QByteArray responseData = reply->readAll();    

    return QJsonDocument::fromJson(responseData);
}
