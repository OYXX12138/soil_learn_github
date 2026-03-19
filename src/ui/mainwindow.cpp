#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QSerialPortInfo>
#include <databasemanager.h>
#include <MvCameraControl.h>
#include "hikcamera.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    HikCamera *hik = new HikCamera(this);
    hik->enumDevices();

    m_workerThread = new QThread(this);
    m_worker = new SerialWorker();
    m_worker->moveToThread(m_workerThread);

    connect(this, &MainWindow::operateSerialPort, m_worker, &SerialWorker::openPort);
    connect(this, &MainWindow::closeSerialPort, m_worker, &SerialWorker::closePort);

    connect(m_worker, &SerialWorker::dataReceived, this, &MainWindow::handleDataReceived);

    connect(m_worker, &SerialWorker::statusChanges, this, &MainWindow::handleStatusChanges);

    connect(m_workerThread, &QThread::finished, m_worker, &QObject::deleteLater);

    m_workerThread->start();

    ui->cboxPorts->clear();
    const auto infos = QSerialPortInfo::availablePorts();
    for(const QSerialPortInfo &info : infos)
    {
        ui->cboxPorts->addItem(info.portName());
    }

    if(ui->cboxPorts->count() == 0)
    {
        ui->cboxPorts->addItem("no serial");
        ui->cboxPorts->addItem("test");
    }
}

MainWindow::~MainWindow()
{
    if(m_workerThread->isRunning())
    {
        m_workerThread->quit();
        m_workerThread->wait();
    }
    delete ui;
}

void MainWindow::handleDataReceived(SensorData data)
{
    qDebug() << "UI收到数据->N:" << data.n << "时间:" << data.dateTime.toString("hh:mm:ss");

    ui->lcdN->display(data.n);
    ui->lcdP->display(data.p);
    ui->lcdK->display(data.k);

    ui->mapView->addTrajectoryPoint(data);

    bool success = DatabaseManager::instance().insertData(data);
    if (!success)
    {
        qDebug() << "警告_数据存入失败";
    }
}

void MainWindow::handleStatusChanges(bool connected, QString message)
{
    ui->lblStatus->setText(message);

    if(!connected)
    {
        ui->btnOpen->setEnabled(false);
        ui->btnClose->setEnabled(true);
    }
}

void MainWindow::on_btnOpen_clicked()
{
    QString portName =  ui->cboxPorts->currentText();
    emit operateSerialPort(portName);

    ui->btnOpen->setEnabled(false);
    ui->btnClose->setEnabled(true);
}

void MainWindow::on_btnClose_clicked()
{
    QString portName =  ui->cboxPorts->currentText();
    emit closeSerialPort(portName);

    ui->btnOpen->setEnabled(true);
    ui->btnClose->setEnabled(false);
}


/*
#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ============================================
    // 核心：多线程组装流水线 (面试必问)
    // ============================================

    // 1. 创建线程对象 (分配一个独立的工作间)
    m_workerThread = new QThread(this);

    // 2. 创建工人对象 (招募一个工人)
    // 注意：这里不能指定 parent，因为一旦指定了 parent，它就没法移动到别的线程了
    m_worker = new SerialWorker();

    // 3. 【魔法时刻】把工人移动到子线程
    m_worker->moveToThread(m_workerThread);

    // 4. 信号槽连接 (牵电话线)

    // 4.1 主线程 -> 子线程：控制命令
    // 当我们发 operateSerialPort 信号时，子线程执行 openPort
    connect(this, &MainWindow::operateSerialPort, m_worker, &SerialWorker::openPort);

    // 4.2 子线程 -> 主线程：数据汇报
    // 当工人发 dataReceived 时，主线程执行 handleDataReceived 更新界面
    connect(m_worker, &SerialWorker::dataReceived, this, &MainWindow::handleDataReceived);

    // 4.3 子线程 -> 主线程：状态汇报
    connect(m_worker, &SerialWorker::statusChanged, this, &MainWindow::handleStatusChanged);

    // 4.4 资源清理 (重要！)
    // 当线程结束时(finished)，自动删除 m_worker 对象，防止内存泄漏
    connect(m_workerThread, &QThread::finished, m_worker, &QObject::deleteLater);

    // 5. 启动线程
    // 此时，SerialWorker 已经在后台待命了，但还没打开串口
    m_workerThread->start();

    ui->cboxPorts->clear();
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos) {
        ui->cboxPorts->addItem(info.portName());
    }

    // 如果一个串口都没找到，加个提示
    if (ui->cboxPorts->count() == 0) {
        ui->cboxPorts->addItem("无串口");
        ui->btnOpen->setEnabled(false);

}

MainWindow::~MainWindow()
{
    // 优雅地结束线程 (标准写法)
    if (m_workerThread->isRunning()) {
        m_workerThread->quit(); // 告诉线程：干完手头的活就下班
        m_workerThread->wait(); // 主线程等待：等你真正下班了我再走
    }
    delete ui;
}

// === 处理数据的槽函数 ===
void MainWindow::handleDataReceived(SensorData data)
{
    // 这里是主线程，可以安全地操作 UI
    qDebug() << "UI收到数据 -> N:" << data.n << " 时间:" << data.timestamp.toString("hh:mm:ss");

    // 比如：ui->labelN->setText(QString::number(data.n));
    // 暂时我们没有 UI 控件，只看 Log
}

void MainWindow::handleStatusChanged(bool connected, QString msg)
{
    qDebug() << "串口状态更新:" << msg;
    // 以后可以在这里修改状态栏颜色
    // if (connected) ui->statusBar->showMessage("正常");
}*/




