#include "vedioview.h"
#include <QDebug>

VedioView::VedioView(QWidget *parent) : QWidget(parent)
{
    initUI();
    initConnection();
}

VedioView::~VedioView()
{

}

void VedioView::initUI()
{
    // 视频播放框（网格）
    vedioGrid = new QGridLayout(this);
    vedioGrid->setSpacing(10);
    vedioGrid->setContentsMargins(5, 5, 5, 5);

    for (int i = 0; i < MAX_VEDIO; ++i)
    {
        Video[i] = new QLabel();
        Video[i]->setMinimumSize(300, 220);
        Video[i]->setAlignment(Qt::AlignCenter);
        Video[i]->setStyleSheet("background-color: #101010; border: 1px solid #404040; border-radius: 8px;");
        Video[i]->setScaledContents(true);
        vedioGrid->addWidget(Video[i], i / 2, i % 2);
    }
}

void VedioView::initConnection()
{

}

void VedioView::getImage(int idx, QImage img)
{
    Video[idx]->setPixmap(QPixmap::fromImage(img));
}
