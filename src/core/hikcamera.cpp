#include "hikcamera.h"

HikCamera::HikCamera(QObject *parent) : QObject(parent)
{
    m_hDevice = NULL;
    memset(&m_deviceList, 0, sizeof(MV_CC_DEVICE_INFO));
}

HikCamera::~HikCamera()
{

}

void HikCamera::enumDevices()
{
    QStringList nDeviceName;

    int nRet = MV_CC_EnumDevices(MV_GIGE_DEVICE | MV_USB_DEVICE, &m_deviceList);

    if (nRet != MV_OK)
    {
        emit errorOccured(QString("寻找相机失败_错误代码_1%").arg(nRet));
        return;
    }

    if (m_deviceList.nDeviceNum == 0)
    {
        qDebug() << "未找到相机_";
        emit foundDevices(nDeviceName);
        return;
    }

    for (int i = 0; i < m_deviceList.nDeviceNum; i++)
    {
        MV_CC_DEVICE_INFO *m_pDeviceInfo = m_deviceList.pDeviceInfo[i];

        if (m_pDeviceInfo->nTLayerType == MV_GIGE_DEVICE)
        {
            int ip1 = ((m_pDeviceInfo->SpecialInfo.stGigEInfo.nCurrentIp & 0xff000000) >> 24);
            int ip2 = ((m_pDeviceInfo->SpecialInfo.stGigEInfo.nCurrentIp & 0x00ff0000) >> 16);
            int ip3 = ((m_pDeviceInfo->SpecialInfo.stGigEInfo.nCurrentIp & 0x0000ff00) >> 8);
            int ip4 = m_pDeviceInfo->SpecialInfo.stGigEInfo.nCurrentIp & 0x000000ff;

            QString IP = QString("%1.%2.%3.%4").arg(ip1).arg(ip2).arg(ip3).arg(ip4);
            QString serialNum = QString((char *)m_pDeviceInfo->SpecialInfo.stGigEInfo.chSerialNumber);

            nDeviceName.append(QString("网口相机[%1]  IP[%2]").arg(serialNum).arg(IP));
        }

        if (m_pDeviceInfo->nTLayerType == MV_USB_DEVICE)
        {
            QString serialNum = QString((char*)m_pDeviceInfo->SpecialInfo.stUsb3VInfo.chSerialNumber);
            nDeviceName.append(QString("USB相机[%1]").arg(serialNum));
        }
    }
    qDebug() << "扫描完毕，找到相机_" << nDeviceName;
    emit foundDevices(nDeviceName);
}
