#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QList>

#define port 6666

class tcpserver : public QObject
{
    Q_OBJECT
public:
    explicit tcpserver(QObject *parent = nullptr);
    ~tcpserver();
    const QMap<QString, QTcpSocket *> &get_clientMap() const {return clientMap;}

private:
    QTcpServer *tcp_server;
    QMap<QString, QTcpSocket *> clientMap;
    void initTcpserver();

private slots:
    void newConnection_slot();

signals:

};

#endif // TCPSERVER_H
