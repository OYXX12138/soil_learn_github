QT       += core gui sql serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# 1. 定义生成路径（让编译产生的乱七八糟文件去 build 文件夹，保持干净）
DESTDIR = $$PWD/bin
MOC_DIR = $$PWD/build/moc
OBJECTS_DIR = $$PWD/build/obj
UI_DIR = $$PWD/build/ui

# 2. 告诉项目去哪里找头文件
INCLUDEPATH += $$PWD/src/core \
               $$PWD/src/ui \
               $$PWD/src/model

# 3. 这里以后会不断增加新文件
SOURCES += \
    main.cpp \
    src/core/databasemanager.cpp \
    src/core/hikcamera.cpp \
    src/core/serialworker.cpp \
    src/ui/mainwindow.cpp \
    src/ui/mapview.cpp

HEADERS += \
    src/core/databasemanager.h \
    src/core/hikcamera.h \
    src/core/serialworker.h \
    src/model/sensordata.h \
    src/ui/mainwindow.h \
    src/ui/mapview.h

FORMS += \
    src/ui/mainwindow.ui

# 1. 定义 SDK 的根目录变量 (请替换为你自己的实际路径！)
HIKVISION_SDK = "D:/Postgraduate/MVS/Development"

# 2. 引入头文件路径 (说明书)
INCLUDEPATH += $$HIKVISION_SDK/Includes

# 3. 链接动态库文件 (引擎)
# -L 表示去哪个目录找，-l (小写L) 表示找哪个名字的库
LIBS += -L$$HIKVISION_SDK/Libraries/win64 -lMvCameraControl

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
