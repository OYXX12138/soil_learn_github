#ifndef SENSORDATA_H
#define SENSORDATA_H

#include <QString>
#include <QDateTime>
#include <QMetaType>

// 这个结构体对应你 MySQL 里的 sensor_records 表
struct SensorData
{
    // 构造函数：给个默认值，防止乱码
    SensorData() : n(0), p(0), k(0), lat(0), lon(0){};

    QString deviceId;      //设备编号
    QDateTime dateTime;    //时间
    double n, p, k;
    double lat, lon;
};

Q_DECLARE_METATYPE(SensorData);

#endif // SENSORDATA_H
