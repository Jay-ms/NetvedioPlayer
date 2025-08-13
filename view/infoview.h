#ifndef INFOVIEW_H
#define INFOVIEW_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>

class InfoView : public QWidget
{
    Q_OBJECT
public:
    QLabel      *currentclientID;
    QLabel      *currentmodeSELECT;
    explicit InfoView(QWidget *parent = nullptr);
    ~InfoView();

private:
    void initUI();
    void initConnection();

    QVBoxLayout *infoLayout;
    QHBoxLayout *currentclientLayout;
    QHBoxLayout *currentmodeLayout;
    QLabel      *currentclientLabel;
    QLabel      *currentmodeLabel;

signals:

};

#endif // INFOVIEW_H
