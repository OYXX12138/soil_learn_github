#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include "serialworker.h"
#include "sensordata.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void operateSerialPort(QString portName);
    void closeSerialPort(QString portName);

private slots:
    void on_btnOpen_clicked();

    void on_btnClose_clicked();

private:
    Ui::MainWindow *ui;

    void handleDataReceived(SensorData data);
    void handleStatusChanges(bool connected, QString message);

    QThread *m_workerThread;
    SerialWorker *m_worker;
};
#endif // MAINWINDOW_H
