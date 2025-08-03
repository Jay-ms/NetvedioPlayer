#include "ffmpegutils.h"
#include <QDebug>
#include <QThread>

ffmpegutils::ffmpegutils(QObject *parent) : QObject(parent)
{
    m_isPlay = false;
}

ffmpegutils::~ffmpegutils()
{
    MyFFmpegDestroy();
}

void ffmpegutils::MyFFmpegSetUrl(QString rtspUrl)
{
    m_rtspUrl = rtspUrl;
}

void ffmpegutils::MyFFmpegInfo()
{
    qDebug("------------------------------------------------------------------");
    qDebug("%s", avcodec_configuration());
    qDebug("version: %d", avcodec_version());
    qDebug("------------------------------------------------------------------");
}

int ffmpegutils::MyFFmpegInit()
{
    m_isPlay = true;
    int i;
    int ret  = -1;

    // 获取视频播放URL
    QByteArray byteRtspUrl = m_rtspUrl.toLocal8Bit();
    char *pRtspUrl = byteRtspUrl.data();

    // 初始化网络库
    avformat_network_init();

    // 分配AVFormatContext，它是FFMPEG解封装（flv，mp4，rmvb，avi）功能的结构体
    m_AVFormatContext = avformat_alloc_context();

    // 设置解封装参数
    AVDictionary *options = NULL;
    // 设置传输协议为TCP协议
    av_dict_set(&options, "rtsp_transport", "tcp", 0);
    // 设置TCP连接最大延时时间
    av_dict_set(&options, "max_delay", "100", 0);
    // 设置“buffer_size”缓存容量
    av_dict_set(&options, "buffer_size", "1024000", 0);
    // 设置avformat_open_input超时时间为3秒
    av_dict_set(&options, "stimeout", "3000000", 0);
    // 打开网络流或文件流
    ret = avformat_open_input(&m_AVFormatContext, pRtspUrl, NULL, &options);
    if(ret != 0)
    {
        m_isPlay = false;
        emit SenderrorMessage(-1);
        return -1;
    }
    // 读取流数据包并获取流的相关信息
    if(avformat_find_stream_info(m_AVFormatContext, NULL) < 0)
    {
        m_isPlay = false;
        emit SenderrorMessage(-2);
        return -2;
    }
    // 确定流格式是否为视频
    for(i = 0; i < m_AVFormatContext->nb_streams; i ++)
    {
        if(m_AVFormatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            m_videoIndex = i;
            break;
        }
    }
    if(m_videoIndex == -1)
    {
        m_isPlay = false;
        emit SenderrorMessage(-3);
        return -3;
    }
    // 1.获取 AVCodecParameters
    AVCodecParameters *codecpar = m_AVFormatContext->streams[m_videoIndex]->codecpar;
    // 2.根据编码器的ID号查找对应的解码器
    m_AVCodec = avcodec_find_decoder(codecpar->codec_id);
    if(!m_AVCodec)
    {
        m_isPlay = false;
        emit SenderrorMessage(-4);
        return -4;
    }
    // 3.分配 AVCodecContext
    m_AVCodecContext = avcodec_alloc_context3(m_AVCodec);
    if(!m_AVCodecContext)
    {
        m_isPlay = false;
        emit SenderrorMessage(-5);
        return -5;
    }
    // 4.拷贝 codecpar 中的参数到 codec context
    if (avcodec_parameters_to_context(m_AVCodecContext, codecpar) < 0)
    {
        m_isPlay = false;
        emit SenderrorMessage(-6);
        return -6;
    }
    // 5.打开解码器
    if(avcodec_open2(m_AVCodecContext, m_AVCodec, NULL) < 0)
    {
        m_isPlay = false;
        emit SenderrorMessage(-7);
        return -7;
    }

    // alloc AVFrame
    m_AVFrame = av_frame_alloc();
    m_AVFrameRGB = av_frame_alloc();

    // 图像色彩空间转换上下文结构体、分辨率缩放、前后图像滤波处理
    m_SwsContext = sws_getContext(m_AVCodecContext->width,m_AVCodecContext->height,
                                  m_AVCodecContext->pix_fmt, m_AVCodecContext->width,
                                  m_AVCodecContext->height, AV_PIX_FMT_RGB32, SWS_BICUBIC,
                                  NULL, NULL, NULL);
    // 计算图像缓冲区大小
    int bytes = av_image_get_buffer_size(AV_PIX_FMT_RGB32, m_AVCodecContext->width, m_AVCodecContext->height, 1);
    m_OutBuffer = (uint8_t *)av_malloc(bytes * sizeof(uint8_t)); // 申请输出缓冲区

    // 将分配的内存空间给m_AVFrameRGB使用
    av_image_fill_arrays(m_AVFrameRGB->data,m_AVFrameRGB->linesize,
                         m_OutBuffer, AV_PIX_FMT_RGB32,
                         m_AVCodecContext->width, m_AVCodecContext->height, 1);

    // 为AVPacket分别内存空间
    m_AVPacket = av_packet_alloc();
    if (!m_AVPacket)
    {
        m_isPlay = false;
        emit SenderrorMessage(-8);
        return -8;
    }

    qDebug()<<"============== (1)MyFFmpegInit ok! ====================== ";
    MyFFmpepReadFrame();
    return 0;
}

void ffmpegutils::MyFFmpegDestroy()
{
    if (m_OutBuffer) {
        av_free(m_OutBuffer);
        m_OutBuffer = nullptr;
    }

    if (m_AVFrame) {
        av_frame_free(&m_AVFrame);
    }

    if (m_AVFrameRGB) {
        av_frame_free(&m_AVFrameRGB);
    }

    if (m_SwsContext) {
        sws_freeContext(m_SwsContext);
        m_SwsContext = nullptr;
    }

    if (m_AVPacket) {
        av_packet_unref(m_AVPacket);
        m_AVPacket = nullptr;
    }

    if (m_AVCodecContext) {
        avcodec_free_context(&m_AVCodecContext);
    }

    if (m_AVFormatContext) {
        avformat_close_input(&m_AVFormatContext);
    }

    avformat_network_deinit();
    qDebug()<<"============== (6)MyFFmpegDestroy finished ============== ";
}

/*
 * @brief MyFFmpeg::MyFFmpepReadFrame 读取一帧数据
 * @return
 */
void ffmpegutils::MyFFmpepReadFrame()
{
    qDebug()<<"============== (2)MyFFmpepReadFrame Start! ============== ";
    int ret = -1;
    while(m_isPlay)
    {
        ret = av_read_frame(m_AVFormatContext, m_AVPacket); // 读取视频流压缩包
        if(ret < 0)
        {
            qDebug("av_read_frame fail!\n");
            break;
        }

        if(m_AVPacket->stream_index == m_videoIndex)
        {
            ret = avcodec_send_packet(m_AVCodecContext, m_AVPacket);    // 将视频流压缩包发送至解码器
            if(ret < 0)
            {
                qDebug("Error sending packet to decoder: %d", ret);
                av_packet_unref(m_AVPacket);
                continue;
            }

            while(ret >= 0)
            {
                ret = avcodec_receive_frame(m_AVCodecContext, m_AVFrame); // 读取解码视频帧
                if(ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
                {
                    break;
                }
                else if(ret < 0)
                {
                    qDebug("Error during decoding: %d", ret);
                    break;
                }

                sws_scale(m_SwsContext, (uint8_t const * const *)m_AVFrame->data, // 转换视频s格式
                             m_AVFrame->linesize, 0, m_AVCodecContext->height,
                             m_AVFrameRGB->data, m_AVFrameRGB->linesize);

                QImage image((uchar *)m_OutBuffer, m_AVCodecContext->width,
                                        m_AVCodecContext->height, QImage::Format_RGB32);

                emit MyFFmpegSigGetOneFrame(image.copy());
            }
        }
        av_packet_unref(m_AVPacket);
    }
    emit MyVediofinished();
    qDebug()<<"============== (4)Read frame loop finished ============== ";
}
