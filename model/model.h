#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QThread>
#include "tcpserver.h"
#include "ffmpegutils.h"
#include "sqliteoperator.h"

#define MAX_STREAMS 4

class model : public QObject
{
    Q_OBJECT
public:
    QString client_id = "device1";
    int idx = 0;

    explicit model(QObject *parent = nullptr);
    ~model();
    tcpserver *gettcpserver() {return m_tcpserver;}
    sqliteoperator *getsqliteoperator() {return m_sqlitedb;}

public slots:
    void handleStartbtnSignal(QString view_url);
    void handleStopbtnSignal();
    void handleFinishedvideo();

private:
    // ffmpeg
    ffmpegutils *m_ffmpeg[MAX_STREAMS];
    QThread     *m_thread[MAX_STREAMS];
    // tcp
    tcpserver *m_tcpserver;
    //sqlite
    sqliteoperator *m_sqlitedb;

signals:
    void SendImage(int idx, QImage img);
    void SendFinishvideo(int idx);
    void SendErrorcodes(int error);
};

#endif // MODEL_H
