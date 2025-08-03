#ifndef VEDIOVIEW_H
#define VEDIOVIEW_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QImage>
#define  MAX_VEDIO 4

class VedioView : public QWidget
{
    Q_OBJECT
public:
    explicit VedioView(QWidget *parent = nullptr);
    ~VedioView();

private:
    void initUI();
    void initConnection();

    QGridLayout *vedioGrid;
    QLabel      *Video[MAX_VEDIO];

public slots:
    void getImage(int idx, QImage img);

signals:

};

#endif // VEDIOVIEW_H
