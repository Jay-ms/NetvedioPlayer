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
    connect(c_view->getControlbtnView(), &ControlbtnView::servoOperationstatus, this, &controller::handleServostatus);
    connect(c_view->getControlbtnView(), &ControlbtnView::systemWorkmodes, this, &controller::handleWorkmodes);
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
