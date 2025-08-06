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
    connect(c_view->getControlbtnView(), &ControlbtnView::catchbtnSignal, this, &controller::handleSendCathch);
    connect(c_view->getControlbtnView(), &ControlbtnView::SpeedChanged, this, [=](int value){speedvalue = value;});

    // controller -> model
    connect(this, &controller::viewSendStart, c_model, &model::handleStartbtnSignal);

    // view -> controller -> model
    connect(c_view->getControlbtnView(), &ControlbtnView::servoOperationstatus, this, &controller::handleServostatus);
    connect(c_view->getControlbtnView(), &ControlbtnView::systemWorkmodes, this, &controller::handleWorkmodes);
    connect(c_view->getControlbtnView(), &ControlbtnView::selectClients, this, &controller::handleSelectclients);
    connect(c_view->getControlbtnView(), &ControlbtnView::stopbtnSignal, c_model, &model::handleStopbtnSignal);

    // model -> controller -> view
    connect(c_model, &model::SendImage, c_view->getVedioView(), &VedioView::getImage);
    connect(c_model, &model::SendFinishvideo, c_view->getVedioView(), &VedioView::getFinishedvideo);
    connect(c_model, &model::SendErrorcodes, c_view, &view::getErrorcodes);
}

void controller::handleSendStart()
{
    QString url = c_view->getUrlView()->rtspUrladdrCombox->currentText();
    if(c_view->getUrlView()->rtspUrladdrCombox->findText(url) == -1)
        c_view->getUrlView()->rtspUrladdrCombox->addItem(url);
    emit viewSendStart(url);
}

void controller::handleSendCathch()
{
    if (c_model->idx < 0 || c_model->idx >= MAX_STREAMS) return;
    if (c_view->getVedioView()->currentFrame[c_model->idx].isNull()) {
        QMessageBox::warning(c_view, "警告", "当前图像为空，无法保存！");
        return;
    }
    QString fileName = QFileDialog::getSaveFileName(c_view,
                        tr("保存图像"),
                        QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss") + ".png",
                        tr("PNG 图像 (*.png);;JPEG 图像 (*.jpg)"));

    if (!fileName.isEmpty()) {
        if (c_view->getVedioView()->currentFrame[c_model->idx].save(fileName)) {
            QMessageBox::information(c_view, "成功", "图像已保存到：\n" + fileName);
        } else {
            QMessageBox::warning(c_view, "错误", "图像保存失败！");
        }
    }
}

void controller::handleServostatus(ServoStatus sta)
{
    const auto &clients = c_model->gettcpserver()->get_clientMap();
    switch (sta) {
        case SERVO_UP:
            if (!clients.isEmpty() && clients[c_model->client_id]) {
                std::string message = "up" + std::to_string(this->speedvalue) + "\n";
                clients[c_model->client_id]->write(message.c_str());
                qDebug() << "向上移动";
            }
            break;
            // 处理向上移动
        case SERVO_DOWN:
            if (!clients.isEmpty() && clients[c_model->client_id]) {
                std::string message = "down" + std::to_string(this->speedvalue) + "\n";
                clients[c_model->client_id]->write(message.c_str());
                qDebug() << "向下移动";
            }
            break;
            // 处理向下移动
        case SERVO_LEFT:
            if (!clients.isEmpty() && clients[c_model->client_id]) {
                std::string message = "left" + std::to_string(this->speedvalue) + "\n";
                clients[c_model->client_id]->write(message.c_str());
                qDebug() << "向左移动";
            }
            break;
            // 处理向左移动
        case SERVO_RIGHT:
            if (!clients.isEmpty() && clients[c_model->client_id]) {
                std::string message = "right" + std::to_string(this->speedvalue) + "\n";
                clients[c_model->client_id]->write(message.c_str());
                qDebug() << "向右移动";
            }
            break;
            // 处理向右移动
        case SERVO_RESET:
            if (!clients.isEmpty() && clients[c_model->client_id]) {
                std::string message = "Reset" + std::to_string(this->speedvalue) + "\n";
                clients[c_model->client_id]->write(message.c_str());
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
    c_view->getInfoView()->currentclientID->setText(QString::number(c_model->idx));
}
