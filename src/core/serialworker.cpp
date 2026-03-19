#include "serialworker.h"

SerialWorker::SerialWorker(QObject *parent) : QObject(parent)
{
    m_serial = new QSerialPort(this);

    m_simulationTimer = new QTimer(this);

    m_isSimulationMode = false;

    connect(m_serial, &QSerialPort::readyRead, this, &SerialWorker::onReadyRead);

    connect(m_simulationTimer, &QTimer::timeout, this, &SerialWorker::onReadyRead);
}

SerialWorker::~SerialWorker()
{
    closePort();
}

void SerialWorker::openPort(QString portName)
{
    if(m_serial->isOpen())
    {
        m_serial->close();
    }

    if(portName == "no serial" || portName == "test" || portName.isEmpty())
    {
        m_isSimulationMode = true;
        emit statusChanges(true, "串口已打开");

        m_simulationTimer->start(1000);
        //onReadyRead();
        return;
    }

    // 配置串口参数（通常是固定的 9600-8-N-1）
    m_isSimulationMode = false;
    m_serial->setPortName(portName);
    m_serial->setBaudRate(QSerialPort::Baud9600);
    m_serial->setDataBits(QSerialPort::Data8);
    m_serial->setParity(QSerialPort::NoParity);
    m_serial->setStopBits(QSerialPort::OneStop);
    m_serial->setFlowControl(QSerialPort::NoFlowControl);

    if(m_serial->open(QIODevice::ReadWrite))
    {
        qDebug() << "串口打开成功:" << portName;
        emit statusChanges(true, "已连接：" + portName);
    }
    else
    {
        qDebug() << "串口打开失败" << m_serial->errorString();
        emit statusChanges(false, "连接失败:" + m_serial->errorString());
    }
}

void SerialWorker::closePort()
{
    if(m_simulationTimer->isActive())
    {
        m_simulationTimer->stop();
    }

    if(m_serial->isOpen())
    {
        m_serial->close();
        emit statusChanges(false, "连接断开");
    }

    emit statusChanges(false, "serial closed");
}

void SerialWorker::onReadyRead()
{
    if(m_isSimulationMode == false && m_serial->isOpen())
    {
        QByteArray rawData = m_serial->readAll();
    }

//    if(rawData.isEmpty())
//    {
//        return;
//    }

    SensorData data;
    data.deviceId = "DEV_001";
    data.dateTime = QDateTime::currentDateTime();

    // 生成一些稍微变化的假数据用来测试
    data.n = 10.0 + (rand() % 50) / 10.0; // 10.0 ~ 15.0
    data.p = 5.0 + (rand() % 50) / 10.0;
    data.k = 20.0 + (rand() % 50) / 10.0;
    data.lat = 39.9042 + (rand() % 100) / 10000.0; // 北京附近
    data.lon = 116.4074 + (rand() % 100) / 10000.0;

    qDebug() << "Worker收到数据->N:" << data.n << " -> 生成模拟数据";

    // 2. 发送给主线程
    emit dataReceived(data);
}

