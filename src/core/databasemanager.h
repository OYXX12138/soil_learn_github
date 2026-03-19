//面试考点：为什么要单例？答：数据库连接是重资源，全局只需要一个连接池，避免重复连接浪费资源。
#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include "sensordata.h"

class DatabaseManager : public QObject
{
    Q_OBJECT

public:
    static DatabaseManager& instance();

    bool connectToDb(const QString &host, const QString &dbName, const QString &user, const QString &password);

    bool insertData(const SensorData &data);

private:
    DatabaseManager(QObject *parent = nullptr);
    ~DatabaseManager();

    DatabaseManager (const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;

    QSqlDatabase m_db;
};

#endif // DATABASEMANAGER_H
