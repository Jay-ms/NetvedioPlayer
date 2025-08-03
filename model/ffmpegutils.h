#ifndef FFMPEGUTILS_H
#define FFMPEGUTILS_H

#include <QObject>
#include <QImage>

#define __STDC_CONSTANT_MACROS

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavfilter/avfilter.h>
#include <libavutil/frame.h>
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>
}

class ffmpegutils : public QObject
{
    Q_OBJECT
public:
    explicit ffmpegutils(QObject *parent = nullptr);
    ~ffmpegutils();

    void MyFFmpegSetUrl(QString rtspUrl);
    void MyFFmpegInfo();

    Q_INVOKABLE int   MyFFmpegInit();
    Q_INVOKABLE void  MyFFmpegDestroy();
    Q_INVOKABLE void  MyFFmpepReadFrame();

    std::atomic_bool m_isPlay;

signals:
    void MyFFmpegSigGetOneFrame(QImage img);
    void MyVediofinished();
    void SenderrorMessage(int err);

private:
    int              m_videoIndex;
    QString          m_rtspUrl;
    const AVCodec    *m_AVCodec;
    AVFormatContext  *m_AVFormatContext;
    AVCodecContext   *m_AVCodecContext;
    AVFrame          *m_AVFrame;
    AVFrame          *m_AVFrameRGB;
    AVPacket         *m_AVPacket;
    SwsContext       *m_SwsContext;
    uint8_t          *m_OutBuffer;
    AVPixelFormat    ConvertDeprecatedFormat(enum AVPixelFormat format);
};

#endif // FFMPEGUTILS_H
