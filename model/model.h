#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QThread>
#include "tcpserver.h"
#include "ffmpegutils.h"
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

public slots:
    void handleStartbtnSignal(QString view_url);

private:
    // ffmpeg
    ffmpegutils *m_ffmpeg[MAX_STREAMS];
    QThread     *m_thread[MAX_STREAMS];
    // tcp
    tcpserver *m_tcpserver;

signals:
    void SendImage(int idx, QImage img);

};

#endif // MODEL_H
