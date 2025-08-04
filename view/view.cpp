#include "view.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

view::view(QWidget *parent) : QWidget(parent)
{
    initUI();
    initConnection();
}

view::~view()
{

}

// 主窗口初始化
void view::initUI()
{
    // 主布局
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(10, 10, 10, 10);
    mainLayout->setSpacing(15);

    // 左右窗
    leftWidget = new QWidget(this);
    rightWidget = new QWidget(this);
    urlview = new UrlView(this);
    vedioview = new VedioView(this);
    controlbtnview = new ControlbtnView(this);
    infoview = new InfoView(this);

    mainLayout->addWidget(leftWidget, 1);
    mainLayout->addWidget(rightWidget);

    // 左窗布局
    QVBoxLayout *leftWidgetLayout = new QVBoxLayout(leftWidget);
    leftWidgetLayout->addWidget(urlview, 0);
    leftWidgetLayout->addWidget(vedioview, 1);

    // 右窗布局
    QVBoxLayout *rightWidgetLayout = new QVBoxLayout(rightWidget);
    rightWidgetLayout->addWidget(controlbtnview);
    rightWidgetLayout->addWidget(infoview);
    rightWidgetLayout->addStretch();
}

// 设置信号与操连接
void view::initConnection()
{

}

void view::getErrorcodes(int err)
{
    switch (err) {
        case -1: QMessageBox::warning(this, "warning", "Couldn't open input strem", QMessageBox::Ok);break;
        case -2: QMessageBox::warning(this, "warning", "Couldn't find stream information", QMessageBox::Ok);break;
        case -3: QMessageBox::warning(this, "warning", "Didn't find a vedio stream", QMessageBox::Ok);break;
        case -4: QMessageBox::warning(this, "warning", "avcodec_find_decoder AV_CODEC_ID_H264 fail!", QMessageBox::Ok);break;
        case -5: QMessageBox::warning(this, "warning", "avcodec_alloc_context3 fail!", QMessageBox::Ok);break;
        case -6: QMessageBox::warning(this, "warning", "avcodec_parameters_to_context fail!", QMessageBox::Ok);break;
        case -7: QMessageBox::warning(this, "warning", "avcodec_open2 fail", QMessageBox::Ok);break;
        case -8: QMessageBox::warning(this, "warning", "Failed to allocate AVPacket", QMessageBox::Ok);break;
        default: break;
    }
    this->getUrlView()->rtspUrladdrCombox->setDisabled(false);
}
