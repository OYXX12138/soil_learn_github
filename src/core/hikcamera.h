#ifndef HIKCAMERA_H
#define HIKCAMERA_H

#include <QObject>
#include <MvCameraControl.h>
#include <QString>
#include <QStringList>
#include <QDebug>

class HikCamera : public QObject
{
    Q_OBJECT
public:
    explicit HikCamera(QObject *parent = nullptr);
    ~HikCamera();

    void enumDevices();

signals:
    void foundDevices(QStringList nDeviceName);

    void errorOccured(QString errorMsg);

private:
    void *m_hDevice;
    MV_CC_DEVICE_INFO_LIST m_deviceList;
};

#endif // HIKCAMERA_H
