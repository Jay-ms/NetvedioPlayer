#include "tcpserver.h"
#include <QDebug>

tcpserver::tcpserver(QObject *parent) : QObject(parent)
{
    initTcpserver();
}

tcpserver::~tcpserver()
{
    // 1. close TCP client socket
    for (auto socket : clientMap.values()) {
        if (socket) {
            socket->disconnectFromHost();
            socket->close();
            socket->deleteLater();
        }
    }
    clientMap.clear();  // clear

    // 2. close TCP server
    if (tcp_server) {
        tcp_server->close();
        tcp_server->deleteLater();
        tcp_server = nullptr;
    }

    qDebug() << "tcpserver resources cleaned up";
}

void tcpserver::initTcpserver()
{
    tcp_server = new QTcpServer(this);

    if(tcp_server->listen(QHostAddress::Any, port))     // 后台监听是否有客户端发起连接请求
    {
        qDebug()<<"Monitoring client devices...";
        connect(tcp_server, &QTcpServer::newConnection, this, &tcpserver::newConnection_slot);
    }
    else
    {
        qDebug()<<"fail connect tcp server";
    }
}

void tcpserver::newConnection_slot()
{
    QTcpSocket *s = tcp_server->nextPendingConnection();        // 获取最新连接客户端得套接字
    qDebug() << "New connection from:" << s->peerAddress().toString();                                 // 将获取的套接字存放到客户端容器中（此时已建立起客户端与服务器的连接）
    // 等待客户端发设备编号
    connect(s, &QTcpSocket::readyRead, this, [=]() {
        QByteArray data = s->readAll();
        QString deviceId = QString::fromUtf8(data).trimmed();  // 去掉换行/空格

        if (!clientMap.contains(deviceId)) {
            clientMap[deviceId] = s;
            qDebug() << "Device ID registered:" << deviceId;
        } else {
            qDebug() << "Duplicate device ID:" << deviceId << ", ignored";
            // 可选：你也可以选择覆盖旧连接
        }

        // 一旦收到设备编号，就断开 readyRead，避免后续数据也被这里截胡
        disconnect(s, &QTcpSocket::readyRead, nullptr, nullptr);
    });

    // 连接断开处理
    connect(s, &QTcpSocket::disconnected, this, [=]() {
        // 遍历查找要删除的 key
        QString idToRemove;
        for (auto it = clientMap.begin(); it != clientMap.end(); ++it) {
            if (it.value() == s) {
                idToRemove = it.key();
                break;
            }
        }
        if (!idToRemove.isEmpty()) {
            clientMap.remove(idToRemove);
            qDebug() << "Client disconnected, ID:" << idToRemove;
        }

        s->deleteLater();
    });
}

