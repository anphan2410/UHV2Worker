#include "mainwindow.h"
#include <QApplication>
#include <QHash>
#include <QDebug>
#include <QThread>
#include <windows.h>
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QState>
#include <QStateMachine>
#include "UHV2Worker/uhv2worker.h"

int main(int argc, char *argv[])
{

    UHV2Worker test;

    qDebug() << test.getPortName();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
