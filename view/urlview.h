#ifndef URLVIEW_H
#define URLVIEW_H

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QHBoxLayout>

class UrlView : public QWidget
{
    Q_OBJECT
public:
    QComboBox   *rtspUrladdrCombox;
    explicit UrlView(QWidget *parent = nullptr);
    ~UrlView();

signals:

private:
    void initUI();
    void initConnection();

    QHBoxLayout *urlLayout;
    QLabel      *rtspUrlLabel;
};

#endif // URLVIEW_H
