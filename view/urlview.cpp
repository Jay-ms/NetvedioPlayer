#include "urlview.h"

UrlView::UrlView(QWidget *parent) : QWidget(parent)
{
    initUI();
    initConnection();
}

UrlView::~UrlView()
{

}

void UrlView::initUI()
{
    QStringList list;
    list << "rtsp://admin:qweasdzxc12@192.168.31.103/h264/ch1/main/av_stream"
         << "rtsp://admin:qweasdzxc12@124.222.61.151:7004/h264/ch1/main/av_stream"
         << "rtsp://admin:admin111@192.168.31.104/cam/realmonitor?channel=1&subtype=0"
         << "rtsp://admin:admin111@124.222.61.151:7005/cam/realmonitor?channel=1&subtype=0"
         << "rtsp://192.168.31.101:554/live/0"
         << "rtsp://124.222.61.151:7003/live/0";

    rtspUrlLabel = new QLabel(tr("RTSP URL"));
    rtspUrlLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    rtspUrladdrCombox = new QComboBox;
    rtspUrladdrCombox->addItems(list);
    rtspUrladdrCombox->setCurrentText(rtspUrladdrCombox->itemText(0));
    rtspUrladdrCombox->setEditable(true);

    // 水平布局
    urlLayout = new QHBoxLayout(this);
    urlLayout->setSpacing(10);
    urlLayout->setContentsMargins(5, 5, 5, 5);
    urlLayout->addWidget(rtspUrlLabel);
    urlLayout->addWidget(rtspUrladdrCombox);
}

void UrlView::initConnection()
{

}
