#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QFileDialog>
#include <QMessageBox>
#include <QDateTime>
#include "view/view.h"
#include "model/model.h"

class controller : public QObject
{
    Q_OBJECT
public:
    int speedvalue = 5;
    explicit controller(QObject *parent = nullptr);

    void setModel(model *model){c_model = model;}
    void setView(view *view){c_view = view;}
    void initController();

private:
    model *c_model;
    view  *c_view;

    void initConnections();

public slots:
    void handleSendStart();
    void handleSendCathch();

    void handleServostatus(ServoStatus sta);
    void handleWorkmodes(WorkModes mode);
    void handleSelectclients(Clients clt);

signals:
    void viewSendStart(QString rtsp_url);
    void viewSendStop();

};

#endif // CONTROLLER_H
