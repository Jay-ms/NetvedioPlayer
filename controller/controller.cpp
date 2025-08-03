#include "controller.h"

controller::controller(QObject *parent) : QObject(parent)
{

}

void controller::initController()
{
    if(!c_model || !c_view)
    {
        qWarning() << "视图或模型未设置";
        return;
    }
    initConnections();  // 在完全初始化后建立信号连接
}

void controller::initConnections()
{
    // view -> controller
    connect(c_view->getControlbtnView(), &ControlbtnView::startbtnSignal, this, &controller::handleSendStart);

    // view -> controller -> model
    connect(c_view->getControlbtnView(), &ControlbtnView::servoOperationstatus, this, &controller::handleServostatus);
    connect(c_view->getControlbtnView(), &ControlbtnView::systemWorkmodes, this, &controller::handleWorkmodes);
    connect(c_view->getControlbtnView(), &ControlbtnView::selectClients, this, &controller::handleSelectclients);

    // controller -> model
    connect(this, &controller::viewSendStart, c_model, &model::handleStartbtnSignal);

    // model -> controller -> view
    connect(c_model, &model::SendImage, c_view->getVedioView(), &VedioView::getImage);
}

void controller::handleSendStart()
{
    QString url = c_view->getUrlView()->rtspUrladdrCombox->currentText();
    if(c_view->getUrlView()->rtspUrladdrCombox->findText(url) == -1)
        c_view->getUrlView()->rtspUrladdrCombox->addItem(url);
    emit viewSendStart(url);
}

void controller::handleSendStop()
{

}

void controller::handleSendCathch()
{

}

void controller::handleServostatus(ServoStatus sta)
{
    const auto &clients = c_model->gettcpserver()->get_clientMap();
    switch (sta) {
        case SERVO_UP:
            if (!clients.isEmpty() && clients[c_model->client_id]) {
                clients[c_model->client_id]->write("up\n");
                qDebug() << "向上移动";
            }
            break;
            // 处理向上移动
        case SERVO_DOWN:
            if (!clients.isEmpty() && clients[c_model->client_id]) {
                clients[c_model->client_id]->write("down\n");
                qDebug() << "向下移动";
            }
            break;
            // 处理向下移动
        case SERVO_LEFT:
            if (!clients.isEmpty() && clients[c_model->client_id]) {
                clients[c_model->client_id]->write("left\n");
                qDebug() << "向左移动";
            }
            break;
            // 处理向左移动
        case SERVO_RIGHT:
            if (!clients.isEmpty() && clients[c_model->client_id]) {
                clients[c_model->client_id]->write("right\n");
                qDebug() << "向右移动";
            }
            break;
            // 处理向右移动
        case SERVO_RESET:
            if (!clients.isEmpty() && clients[c_model->client_id]) {
                clients[c_model->client_id]->write("Reset\n");
                qDebug() << "复位";
            }
            break;
            // 处理确认
    }
}

void controller::handleWorkmodes(WorkModes mode)
{
    const auto &clients = c_model->gettcpserver()->get_clientMap();
    switch (mode) {
        case MODE_AUTO:
            if (!clients.isEmpty() && clients[c_model->client_id]) {
                clients[c_model->client_id]->write("auto\n");
                qDebug() << "自动模式";
            }
            break;
            // 自动模式
        case MODE_MANUAL:
            if (!clients.isEmpty() && clients[c_model->client_id]) {
                clients[c_model->client_id]->write("manual\n");
                qDebug() << "手动模式";
            }
            break;
            // 手动模式
    }
}

void controller::handleSelectclients(Clients clt)
{
    switch (clt) {
        case CLIENT1:
            c_model->client_id = "device1";
            c_model->idx = 0;
            qDebug()<<"selected device1";
        break;
        case CLIENT2:
            c_model->client_id = "device2";
            c_model->idx = 1;
            qDebug()<<"selected device2";
        break;
        case CLIENT3:
            c_model->client_id = "device3";
            c_model->idx = 2;
            qDebug()<<"selected device3";
        break;
        case CLIENT4:
            c_model->client_id = "device4";
            c_model->idx = 3;
            qDebug()<<"selected device4";
        break;
    }
}
