#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "model/model.h"
#include "view/view.h"
#include "controller/controller.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void setUI(view *widget);

    model *m_model;
    view *m_view;
    controller *m_controller;

};
#endif // MAINWINDOW_H
