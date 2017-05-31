#include "serialportconnectionestablishment.h"

SerialPortConnectionEstablishment::SerialPortConnectionEstablishment(UHV2Worker *parent, UHV2WorkerVarSet *VarSet)
    : QState(parent), parentPtr(parent), VarSetPtr(VarSet)
{

}

SerialPortConnectionEstablishment::~SerialPortConnectionEstablishment()
{
    parentPtr = Q_NULLPTR;
    VarSetPtr = Q_NULLPTR;
    delete parentPtr;
    delete VarSetPtr;
}

void SerialPortConnectionEstablishment::onEntry(QEvent *)
{
    if (VarSetPtr->SerialPort)
    {
        if (VarSetPtr->SerialPort->isOpen())
        {
            VarSetPtr->SerialPort->close();
        }
    }
    VarSetPtr->SerialPort = new QSerialPort();
    VarSetPtr->configSerialPort();
    if (VarSetPtr->SerialPort->open(QIODevice::ReadWrite))
    {
        emit parentPtr->DirectStateTransitionRequest("SolitaryMessageTransmission");
    }
}
