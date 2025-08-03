#ifndef CONTROLBTNVIEW_H
#define CONTROLBTNVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>

// 定义云台枚举类型
enum ServoStatus {
    SERVO_UP,
    SERVO_DOWN,
    SERVO_LEFT,
    SERVO_RIGHT,
    SERVO_RESET,
};

// 定义系统工作模式枚举类型
enum WorkModes{
    MODE_AUTO,
    MODE_MANUAL,
};

class ControlbtnView : public QWidget
{
    Q_OBJECT
public:
    explicit ControlbtnView(QWidget *parent = nullptr);
    ~ControlbtnView();

private:
    void initUI();
    void initConnection();

    QVBoxLayout *btnLayout;
    // 视频控制按钮
    QHBoxLayout *vediobtnLayout;
    QPushButton *StartButton;
    QPushButton *StopButton;
    QPushButton *SaveButton;

    // 云台控制按钮
    QGridLayout *btnGrid;
    QPushButton *btnUp;
    QPushButton *btnDown;
    QPushButton *btnLeft;
    QPushButton *btnRight;
    QPushButton *btnReset;

    // 模式切换
    QHBoxLayout *modeLayout;
    QPushButton *btnAuto;
    QPushButton *btnManual;

    // 视频接入客户端切换
    QHBoxLayout *clientbtnLayout;
    QPushButton *btnclient1;
    QPushButton *btnclient2;
    QPushButton *btnclient3;
    QPushButton *btnclient4;

signals:
    // 统一云台控制信号
    void servoOperationstatus(ServoStatus sta);
    void systemWorkmodes(WorkModes mode);

};

#endif // CONTROLBTNVIEW_H
