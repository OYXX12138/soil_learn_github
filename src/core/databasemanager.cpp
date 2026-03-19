#include "databasemanager.h"

DatabaseManager::DatabaseManager(QObject *parent) : QObject(parent)
{
    // 这里什么都不做，连接逻辑放在 connectToDb 里
}

DatabaseManager::~DatabaseManager()
{
    if(m_db.isOpen())
    {
        m_db.close();
    }
}

DatabaseManager& DatabaseManager::instance()
{
    static DatabaseManager instance;
    return instance;
}

bool DatabaseManager::connectToDb(const QString &host, const QString &dbName, const QString &user, const QString &password)
{
    if(m_db.isOpen())
    {
        return true;
    }

    m_db = QSqlDatabase::addDatabase("QMYSQL");
    m_db.setHostName(host);
    m_db.setDatabaseName(dbName);
    m_db.setUserName(user);
    m_db.setPassword(password);

    if(!m_db.open())
    {
        qDebug() << "Error: Fail to connect mysql" << m_db.lastError();
        return false;
    }

    qDebug() << "Success: Connect success";
    return true;
}

bool DatabaseManager::insertData(const SensorData &data)
{
    if(!m_db.isOpen())
    {
        qDebug() << "Error: Database isn't open";
        return false;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO sensor_records(device_id, timestamp, n_val, p_val, k_val, latitude, longitude)"
                  "VALUES(?, ?, ?, ?, ?, ?, ?)");

    query.addBindValue(data.deviceId);
    query.addBindValue(data.dateTime);
    query.addBindValue(data.n);
    query.addBindValue(data.p);
    query.addBindValue(data.k);
    query.addBindValue(data.lat);
    query.addBindValue(data.lon);

    if(!query.exec())
    {
        qDebug() << "Insert error" << query.lastError();
        return false;
    }

    return true;
}









