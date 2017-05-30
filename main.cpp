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
#include "UHV2Worker/serialportinforequest.h"
#include "binaryprotocol.h"

int main(int argc, char *argv[])
{




//    QSerialPortInfo port0 = QSerialPortInfo::availablePorts().at(0);

//    QSerialPortInfo port1 = QSerialPortInfo::availablePorts().at(1);
//    qDebug() << port0.portName() << " INFO: " << port0.description();
//    qDebug() << port1.portName() << " INFO: " << port1.description();



//    QSerialPortInfo *testa = new QSerialPortInfo("COM1");

//    qDebug() << testa->isNull() << " and " << testa->isBusy() << " finally " << testa->isValid();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
