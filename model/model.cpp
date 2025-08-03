#include "model.h"

model::model(QObject *parent) : QObject(parent)
{
    m_tcpserver = new tcpserver;
}

model::~model()
{

}

void model::handleStartbtnSignal(QString view_url)
{
    if(idx < 0 || idx >= MAX_STREAMS) return;

    int localIdx = idx;
    m_ffmpeg[localIdx] = new ffmpegutils;
    m_thread[localIdx] = new QThread;
    m_ffmpeg[localIdx]->moveToThread(m_thread[localIdx]);

    connect(m_ffmpeg[localIdx], &ffmpegutils::MyFFmpegSigGetOneFrame, this, [=](QImage img){
        if (!img.isNull()) emit SendImage(localIdx, img);
    });
    connect(m_thread[localIdx], &QThread::finished, m_ffmpeg[localIdx], &QObject::deleteLater);
    connect(m_thread[localIdx], &QThread::finished, m_thread[localIdx], &QObject::deleteLater);

    QString url = view_url;
    if(url.isEmpty())   // 空地址返回
    {
        return;
    }
    m_ffmpeg[idx]->MyFFmpegSetUrl(url);
    m_thread[idx]->start();
    QMetaObject::invokeMethod(m_ffmpeg[localIdx], "MyFFmpegInit");
}
