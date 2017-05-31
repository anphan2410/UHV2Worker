#include "uhv2workervarset.h"

UHV2WorkerVarSet::UHV2WorkerVarSet(QObject *parent)
    : QObject(parent)
{

}

UHV2WorkerVarSet::~UHV2WorkerVarSet()
{
    //please delete PendingMessageList here
    PortName = Q_NULLPTR;
    SerialPort = Q_NULLPTR;
    delete PortName;
    delete SerialPort;
}

void UHV2WorkerVarSet::configSerialPort()
{
    SerialPort->setReadBufferSize(64);
    SerialPort->setDataBits(QSerialPort::Data8);
    SerialPort->setBaudRate(QSerialPort::Baud9600);
    SerialPort->setStopBits(QSerialPort::OneStop);
    SerialPort->setParity(QSerialPort::NoParity);
    SerialPort->setFlowControl(QSerialPort::NoFlowControl);
    SerialPort->setPortName(*PortName);
}
