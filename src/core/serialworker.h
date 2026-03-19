#ifndef SERIALWORKER_H
#define SERIALWORKER_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QDebug>
#include <sensordata.h>
#include <QTimer>

class SerialWorker : public QObject
{
    Q_OBJECT

public:
    explicit SerialWorker(QObject *parent = nullptr);
    ~SerialWorker();

private: signals:
    void statusChanges(bool connected, QString message);
    void dataReceived(SensorData data);
    void errorOccurred(QString errorMsg);

public slots:
    void openPort(QString portName);
    void closePort();

private slots:
    void onReadyRead();

private:
    QSerialPort *m_serial;
    QTimer *m_simulationTimer;
    bool m_isSimulationMode;
};

#endif // SERIALWORKER_H
