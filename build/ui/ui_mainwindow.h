/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "mapview.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QComboBox *cboxPorts;
    QPushButton *btnOpen;
    QPushButton *btnClose;
    QLabel *lblStatus;
    QLCDNumber *lcdN;
    QLCDNumber *lcdP;
    QLCDNumber *lcdK;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    MapView *mapView;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        cboxPorts = new QComboBox(centralwidget);
        cboxPorts->setObjectName(QString::fromUtf8("cboxPorts"));
        cboxPorts->setGeometry(QRect(10, 80, 121, 41));
        btnOpen = new QPushButton(centralwidget);
        btnOpen->setObjectName(QString::fromUtf8("btnOpen"));
        btnOpen->setGeometry(QRect(150, 80, 101, 41));
        btnClose = new QPushButton(centralwidget);
        btnClose->setObjectName(QString::fromUtf8("btnClose"));
        btnClose->setGeometry(QRect(270, 80, 101, 41));
        lblStatus = new QLabel(centralwidget);
        lblStatus->setObjectName(QString::fromUtf8("lblStatus"));
        lblStatus->setGeometry(QRect(40, 200, 231, 21));
        lcdN = new QLCDNumber(centralwidget);
        lcdN->setObjectName(QString::fromUtf8("lcdN"));
        lcdN->setGeometry(QRect(110, 310, 241, 71));
        lcdP = new QLCDNumber(centralwidget);
        lcdP->setObjectName(QString::fromUtf8("lcdP"));
        lcdP->setGeometry(QRect(110, 390, 241, 71));
        lcdK = new QLCDNumber(centralwidget);
        lcdK->setObjectName(QString::fromUtf8("lcdK"));
        lcdK->setGeometry(QRect(110, 470, 241, 71));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(23, 311, 81, 71));
        label->setStyleSheet(QString::fromUtf8("font: 24pt \"Consolas\";"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 390, 81, 71));
        label_2->setStyleSheet(QString::fromUtf8("font: 24pt \"Consolas\";"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 470, 81, 71));
        label_3->setStyleSheet(QString::fromUtf8("font: 24pt \"Consolas\";"));
        mapView = new MapView(centralwidget);
        mapView->setObjectName(QString::fromUtf8("mapView"));
        mapView->setGeometry(QRect(370, 170, 411, 371));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        btnOpen->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\344\270\262\345\217\243", nullptr));
        btnClose->setText(QCoreApplication::translate("MainWindow", "\345\205\263\351\227\255\344\270\262\345\217\243", nullptr));
        lblStatus->setText(QCoreApplication::translate("MainWindow", "\345\260\261\347\273\252", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "N", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "P", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "K", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
