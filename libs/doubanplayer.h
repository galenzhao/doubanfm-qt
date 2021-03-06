#ifndef DOUBANPLAYER_H
#define DOUBANPLAYER_H

#include <QObject>
#include <libs/doubanfm.h>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <ctime>
#include "downloadmanager.h"

class DoubanPlayer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qint64 position READ position NOTIFY positionChanged)
    Q_PROPERTY(qint64 duration READ duration)
    Q_PROPERTY(DoubanFMSong currentSong READ currentSong NOTIFY currentSongChanged)
    Q_PROPERTY(qint32 channel READ channel WRITE setChannel)
    Q_PROPERTY(int volume READ volume WRITE setVolume)
    Q_PROPERTY(QMediaPlayer::State state READ state NOTIFY stateChanged)
    Q_PROPERTY(bool canControl READ canControl NOTIFY canControlChanged)
    Q_PROPERTY(qint32 kbps READ kbps WRITE setKbps)
public:
    static DoubanPlayer& getInstance();
    ~DoubanPlayer();

    qint64 position() const;
    qint64 duration() const;

    const DoubanFMSong& currentSong() const;
    qint32 channel() const;
    int volume() const;
    QMediaPlayer::State state() const;

    qint32 kbps() const;
    bool canControl() const;
    void setSaveMp3File(bool flag);

signals:
    void saveSong(const DoubanFMSong & song, bool flag, const QString & message);
    void currentSongChanged(const DoubanFMSong& song);
    void positionChanged(qint64);

    void receivedSkipSong(bool);
    void receivedRateSong(bool);
    void receivedTrashSong(bool);

    void stateChanged(QMediaPlayer::State);

    void canControlChanged(bool);

    void playing();
    void paused();
    void stopped();
    void canSaveMp3File(bool flag);
    void playNextSong(const DoubanFMSong & song);

public slots:
    void next();
    void pause();
    void play();
    void stop();

    void rateCurrentSong();
    void unrateCurrentSong();
    void trashCurrentSong();

    void setChannel(qint32);
    void setVolume(int);

    void setKbps(qint32);
    void setCanControl(bool);

private slots:
    void currentIndexChanged(int position);
    void saveMp3ToDisk(const QString & filename, const DoubanFMSong & song, bool flag);

private:
    explicit DoubanPlayer(QObject *parent = 0);

    QList<DoubanFMSong> songs;
    QMediaPlayer player;
    DoubanFM& doubanfm;
    qint32 _channel;
    qint32 _volume;
    bool _can_control;

    QMediaPlaylist *bufplaylist;
    QList<DoubanFMSong> bufsongs;

    time_t lastPausedTime;
    qint32 _kbps;

    DownloadManager downloadManager;
    // save mp3 file
    bool saveMp3FileFromSong(const DoubanFMSong & song);
    bool saveID3ForSong(const QString & filename, const DoubanFMSong & song);
    bool saveMp3File;
};

#endif // DOUBANPLAYER_H
