#include "sqliteoperator.h"

sqliteoperator::sqliteoperator(QObject *parent) : QObject(parent)
{
    if(QSqlDatabase::contains("qt_sql_default_connection"))
    {
        urldatabase = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        urldatabase = QSqlDatabase::addDatabase("QSQLITE");
        urldatabase.setDatabaseName("UrlDataBase.db");
    }
    openDB();       // 打开数据库
    createTable();  // 创建数据表urladdrs
}

void sqliteoperator::createTable(void)
{
    QSqlQuery sqlQuery;         // urladdrs不存在才新建、ID自增、url不重复
    QString createSql = ("CREATE TABLE IF NOT EXISTS urladdrs (\
                        id INTEGER  PRIMARY KEY AUTOINCREMENT NOT NULL,\
                        urladdr TEXT NOT NULL UNIQUE)");
    sqlQuery.prepare(createSql);
    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to create table. " << sqlQuery.lastError();
    }
    else
    {
        qDebug() << "Table created!";
    }
}

bool sqliteoperator::openDB(void)
{
    if(!urldatabase.open())
    {
        qDebug() << "Error: Failed to connect database." << urldatabase.lastError();
        return false;
    }
    return true;
}

bool sqliteoperator::isTableExist(QString& tableName)
{
    QSqlDatabase database = QSqlDatabase::database();       // 获取默认连接对象
    if(database.tables().contains(tableName))
        return true;
    return false;
}

QStringList sqliteoperator::queryTable()
{
    QSqlQuery sqlQuery;
    QStringList list;
    sqlQuery.exec("SELECT * FROM urladdrs");
    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to query table. " << sqlQuery.lastError();
    }
    else
    {
        while(sqlQuery.next())
        {
            int id = sqlQuery.value(0).toInt();
            QString urladdr = sqlQuery.value(1).toString();
            list << urladdr;
            qDebug()<<QString("id:%1    urladdr:%2").arg(id).arg(urladdr);
        }
    }
    return list;
}

void sqliteoperator::insertUrlToDb(const QString &url)
{
    QSqlQuery sqlQuery;
    sqlQuery.prepare("INSERT OR IGNORE INTO urladdrs (urladdr) VALUES (:url)");
    sqlQuery.bindValue(":url", url);
    if(!sqlQuery.exec())
    {
        qDebug() << "Insert failed:" << sqlQuery.lastError();
    }

    // 删除多余的数据（保持最多10条）
    sqlQuery.exec("SELECT COUNT(*) FROM urladdrs"); // 查询当前列表行数
    if(sqlQuery.next())
    {
        int count = sqlQuery.value(0).toInt();
        if(count > 10)
        {
            int toDelete = count - 10;
            // 删除最早插入的toDelete条记录（按 id 升序）
            sqlQuery.prepare(QString("DELETE FROM urladdrs WHERE id IN (SELECT id FROM urladdrs ORDER BY id ASC LIMIT %1)").arg(toDelete));
            if(!sqlQuery.exec())
                qDebug() << "Delete old urls failed:" << sqlQuery.lastError();
        }
    }
}

void sqliteoperator::modifyData(int id, QString urladdr)
{
    QSqlQuery sqlQuery;
    sqlQuery.prepare("UPDATE urladdrs SET urladdr=? WHERE id=?");
    sqlQuery.addBindValue(urladdr);
    sqlQuery.addBindValue(id);
    if(!sqlQuery.exec())
    {
        qDebug() << sqlQuery.lastError();
    }
    else
    {
        qDebug() << "updated data success!";
    }
}

void sqliteoperator::deleteData(int id)
{
    QSqlQuery sqlQuery;
    sqlQuery.exec(QString("DELETE FROM urladdrs WHERE id = %1").arg(id));
    if(!sqlQuery.exec())
    {
        qDebug()<<sqlQuery.lastError();
    }
    else
    {
        qDebug()<<"deleted data success!";
    }
}

void sqliteoperator::deleteTable(QString& tableName)
{
    QSqlQuery sqlQuery;
    sqlQuery.prepare(QString("DROP TABLE %1").arg(tableName));
    if(!sqlQuery.exec())
    {
        qDebug() << sqlQuery.lastError();
    }
    else
    {
        qDebug() << "deleted table success";
    }
}

void sqliteoperator::closeDB(void)
{
    urldatabase.close();
}
