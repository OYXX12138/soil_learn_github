#include "mainwindow.h"
#include <QApplication>
#include "databasemanager.h"
#include "sensordata.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qRegisterMetaType<SensorData>("SensorData");
    DatabaseManager::instance().connectToDb("localhost", "mydatabase", "root", "123456");

    MainWindow w;
    w.show();
    return a.exec();
}
