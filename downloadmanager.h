#ifndef DOWNLOADMANAGER_H
#define DOWNLOADMANAGER_H

#include <QObject>
#include <QCoreApplication>
#include <QFile>
#include <QFileInfo>
#include <QList>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QStringList>
#include <QTimer>
#include <QUrl>
#include "libs/douban_types.h"

class DownloadManager : public QObject
{
    Q_OBJECT

    QNetworkAccessManager manager;
        QList<QNetworkReply *> currentDownloads;
        QMap<QNetworkReply *, DoubanFMSong> songsMap;

public:
    explicit DownloadManager(QObject *parent = 0);
        void doDownload(const QUrl &url, const DoubanFMSong & song);
            QString saveFileName(const QUrl &url);
            bool saveToDisk(const QString &filename, QIODevice *data);
signals:
    void saveMp3ToDisk(const QString & filename, const DoubanFMSong & song, bool flag);

public slots:
            void execute();
                void downloadFinished(QNetworkReply *reply);
};

#endif // DOWNLOADMANAGER_H
