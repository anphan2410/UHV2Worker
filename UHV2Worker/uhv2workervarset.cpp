#include "uhv2workervarset.h"

UHV2WorkerVarSet::UHV2WorkerVarSet(QObject *parent)
    : QObject(parent)
{
    qRegisterMetaType<UHV2WorkerVarSet::PrioritizedCommandMessage>("UHV2WorkerVarSet::PrioritizedCommandMessage");
    initialize();
    anDebug("=> Construct A New UHV2WorkerVarSet !");
}

UHV2WorkerVarSet::~UHV2WorkerVarSet()
{
    PendingMessageList->clear();
    PendingMessageList = Q_NULLPTR;
    PortName = Q_NULLPTR;
    SerialPort = Q_NULLPTR;
    lastTransmittedMessage = Q_NULLPTR;
    lastReceivedMessage = Q_NULLPTR;
    delete PortName;
    delete SerialPort;
    delete lastTransmittedMessage;
    delete lastReceivedMessage;
    delete PendingMessageList;
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

void UHV2WorkerVarSet::initialize()
{
    PortName = new QString();
    if (SerialPort)
        if (SerialPort->isOpen())
            SerialPort->close();
    SerialPort = new QSerialPort();
    if (PendingMessageList)
        PendingMessageList->clear();
    PendingMessageList = new QMap<qint8,QList<CommandMessage*>*>();
    ErrorStatus = Nothing;
}
