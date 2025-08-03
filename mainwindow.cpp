#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowIcon(QIcon(":/resources/ico/vedio.ico"));

    m_model = new model();
    m_view = new view(this);
    m_controller = new controller();

    m_controller->setModel(m_model);
    m_controller->setView(m_view);
    m_controller->initController();

    setUI(m_view);
}

MainWindow::~MainWindow()
{

}

void MainWindow::setUI(view *widget)
{
    QString qss = R"(
        QWidget {
            background-color: #2b2b2b;
            color: #f0f0f0;
            font-family: "Segoe UI", "Microsoft YaHei";
            font-size: 14px;
        }
        QLabel {
            color: #e0e0e0;
        }
        QComboBox {
            background-color: #3c3f41;
            border: 1px solid #5c5c5c;
            border-radius: 5px;
            padding: 4px 8px;
        }
        QPushButton {
            background-color: #4c4f52;
            border: none;
            border-radius: 6px;
            padding: 6px;
        }
        QPushButton:hover {
            background-color: #5a5d60;
        }
        QPushButton:pressed {
            background-color: #6a6d70;
        }
    )";

    // 全局配色风格
    this->setStyleSheet(qss);
    this->setCentralWidget(widget);
    this->setWindowTitle("NetVedio Player");
    this->resize(980, 600);
    this->setMinimumSize(960, 540);
}
