#ifndef INFOVIEW_H
#define INFOVIEW_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>

class InfoView : public QWidget
{
    Q_OBJECT
public:
    explicit InfoView(QWidget *parent = nullptr);
    ~InfoView();
private:
    void initUI();
    void initConnection();

    QHBoxLayout *currentclientLayout;
    QLabel      *currentclientLabel;
    QLabel      *currentclientID;

    int idx = 0;

signals:

};

#endif // INFOVIEW_H
