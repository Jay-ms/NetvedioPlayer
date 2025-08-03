#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include "tcpserver.h"
#include "ffmpegutils.h"

class model : public QObject
{
    Q_OBJECT
public:
    QString client_id = "device1";
    int idx = 0;

    explicit model(QObject *parent = nullptr);
    ~model();
    tcpserver *gettcpserver() {return m_tcpserver;}

private:
    tcpserver *m_tcpserver;

signals:

};

#endif // MODEL_H
