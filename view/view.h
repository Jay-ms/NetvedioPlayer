#ifndef VIEW_H
#define VIEW_H

#include <QWidget>
#include <QMessageBox>
#include "urlview.h"
#include "vedioview.h"
#include "controlbtnview.h"
#include "infoview.h"

class view : public QWidget
{
    Q_OBJECT
public:
    explicit view(QWidget *parent = nullptr);
    ~view();

    UrlView *getUrlView() {return urlview;}
    VedioView *getVedioView() {return vedioview;}
    ControlbtnView *getControlbtnView() {return controlbtnview;}
    InfoView *getInfoView() {return infoview;}

private:
    void initUI();
    void initConnection();

    QWidget *leftWidget;
    QWidget *rightWidget;

    UrlView   *urlview;
    VedioView *vedioview;
    ControlbtnView *controlbtnview;
    InfoView *infoview;

public slots:
    void getErrorcodes(int err);

signals:

};

#endif // VIEW_H
