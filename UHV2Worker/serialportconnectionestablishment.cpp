#include "serialportconnectionestablishment.h"

SerialPortConnectionEstablishment::SerialPortConnectionEstablishment(UHV2Worker *parent)
    : QState(parent), parentPtr(parent)
{

}

SerialPortConnectionEstablishment::~SerialPortConnectionEstablishment()
{
    parentPtr = Q_NULLPTR;
    delete parentPtr;
}

void SerialPortConnectionEstablishment::onEntry(QEvent *)
{
    failTimeCount = 0;
    QSerialPort *UHV2SerialPort = new QSerialPort(parentPtr->getPortName());
    if (UHV2SerialPort->isOpen())
        UHV2SerialPort->close();
    while (failTimeCount <= 3)
    {
        if (UHV2SerialPort->open(QIODevice::ReadWrite))
            break;
    }
    if (UHV2SerialPort->isOpen())
    {
        parentPtr->setSerialPort(UHV2SerialPort);
        machine()->postEvent(UHV2Worker::DirectStateTransitionRequest("SendACommand"));
    }
    else
        parentPtr->setErrorStatus(UHV2Worker::SerialPortFailedToOpen);
}
