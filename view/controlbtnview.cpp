#include "controlbtnview.h"

ControlbtnView::ControlbtnView(QWidget *parent) : QWidget(parent)
{
    initUI();
    initConnection();
}

ControlbtnView::~ControlbtnView()
{

}

void ControlbtnView::initUI()
{
    // 视频播放按钮
    vediobtnLayout = new QHBoxLayout();
    StartButton = new QPushButton();
    StartButton->setIcon(QIcon(":/img/resources/img/Start.png"));
    StopButton = new QPushButton();
    StopButton->setIcon(QIcon(":/img/resources/img/Stop.png"));
    SaveButton = new QPushButton();
    SaveButton->setIcon(QIcon(":/img/resources/img/Save.png"));
    vediobtnLayout->addStretch();
    vediobtnLayout->addWidget(StartButton);
    vediobtnLayout->addWidget(StopButton);
    vediobtnLayout->addWidget(SaveButton);
    vediobtnLayout->addStretch();

    // 云台控制按钮
    btnGrid = new QGridLayout();
    btnGrid->setSpacing(4);
    btnUp = new QPushButton();
    btnUp->setIcon(QIcon(":/img/resources/img/Up.png"));
    btnDown = new QPushButton();
    btnDown->setIcon(QIcon(":/img/resources/img/Down.png"));
    btnLeft = new QPushButton();
    btnLeft->setIcon(QIcon(":/img/resources/img/Left.png"));
    btnRight = new QPushButton();
    btnRight->setIcon(QIcon(":/img/resources/img/Right.png"));
    btnReset = new QPushButton();
    btnReset->setIcon(QIcon(":/img/resources/img/Reset.png"));
    btnGrid->addWidget(btnUp, 0, 1);
    btnGrid->addWidget(btnLeft, 1, 0);
    btnGrid->addWidget(btnReset, 1, 1);
    btnGrid->addWidget(btnRight, 1, 2);
    btnGrid->addWidget(btnDown, 2, 1);

    // 模式切换按钮
    modeLayout = new QHBoxLayout();
    btnAuto = new QPushButton();
    btnAuto->setIcon(QIcon(":/img/resources/img/Auto.png"));
    btnManual = new QPushButton();
    btnManual->setIcon(QIcon(":/img/resources/img/Manual.png"));
    modeLayout->addStretch();
    modeLayout->addWidget(btnAuto);
    modeLayout->addWidget(btnManual);
    modeLayout->addStretch();

    // 客户端选择按钮
    clientbtnLayout = new QHBoxLayout();
    QList<QPushButton*> clients;
    btnclient1 = new QPushButton("0"); clients << btnclient1;
    btnclient2 = new QPushButton("1"); clients << btnclient2;
    btnclient3 = new QPushButton("2"); clients << btnclient3;
    btnclient4 = new QPushButton("3"); clients << btnclient4;
    for (auto btn : clients) {
        btn->setFixedSize(40, 24);
        clientbtnLayout->addWidget(btn);
    }

    // 按钮区域
    btnLayout = new QVBoxLayout(this);
    btnLayout->setSpacing(15);
    btnLayout->setContentsMargins(5, 5, 5, 5);
    btnLayout->addLayout(vediobtnLayout);
    btnLayout->addLayout(btnGrid);
    btnLayout->addLayout(modeLayout);
    btnLayout->addLayout(clientbtnLayout);
}

void ControlbtnView::initConnection()
{
    // 发送云台控制按钮信号
    connect(btnUp, &QPushButton::clicked, this, [=](){
        emit servoOperationstatus(SERVO_UP);
    });
    connect(btnDown, &QPushButton::clicked, this, [=](){
        emit servoOperationstatus(SERVO_DOWN);
    });
    connect(btnLeft, &QPushButton::clicked, this, [=](){
        emit servoOperationstatus(SERVO_LEFT);
    });
    connect(btnRight, &QPushButton::clicked, this, [=](){
        emit servoOperationstatus(SERVO_RIGHT);
    });
    connect(btnReset, &QPushButton::clicked, this, [=](){
        emit servoOperationstatus(SERVO_RESET);
    });

    // 发送系统工作模式按钮信号
    connect(btnAuto, &QPushButton::clicked, this, [=](){
        emit systemWorkmodes(MODE_AUTO);
    });
    connect(btnManual, &QPushButton::clicked, this, [=](){
        emit systemWorkmodes(MODE_MANUAL);
    });
}
