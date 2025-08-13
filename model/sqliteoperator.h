#ifndef SQLITEOPERATOR_H
#define SQLITEOPERATOR_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

typedef struct
{
    int id; // RTSP URL 数据 ID
    QString urladdr;
}urldb;

class sqliteoperator : public QObject
{
    Q_OBJECT
public:
    explicit sqliteoperator(QObject *parent = nullptr);
    bool openDB(void);
    void createTable(void);
    bool isTableExist(QString& tableName);
    QStringList queryTable();
    void insertUrlToDb(const QString &url);
    void modifyData(int id, QString urladdr);
    void deleteData(int id);
    void deleteTable(QString& tableName);
    void closeDB(void);

private:
    QSqlDatabase urldatabase;   // 用于建立和数据库的连接

signals:

};

#endif // SQLITEOPERATOR_H
