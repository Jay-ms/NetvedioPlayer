#include "infoview.h"

InfoView::InfoView(QWidget *parent) : QWidget(parent)
{
    initUI();
    initConnection();
}

InfoView::~InfoView()
{

}

void InfoView::initUI()
{
    currentclientLabel = new QLabel("CURRENT ID:");
    currentclientLabel->setStyleSheet(R"(
        QLabel {
            font-weight: bold;
            font-size: 16px;
            color: #9ecfff;
        })");
    currentclientID = new QLabel(QString::number(idx));
    currentclientID->setFixedWidth(50);
    currentclientID->setAlignment(Qt::AlignCenter);
    currentclientID->setStyleSheet(R"(
        QLabel {
            background-color: #3c4c5c;
            border: 1px solid #5c7fa3;
            color: white;
            border-radius: 8px;
            font-weight: bold;
            font-size: 16px;
            padding: 4px;
        })");

    currentclientLayout = new QHBoxLayout(this);
    currentclientLayout->addWidget(currentclientLabel);
    currentclientLayout->addWidget(currentclientID);
    currentclientLayout->addStretch();
}

void InfoView::initConnection()
{

}
