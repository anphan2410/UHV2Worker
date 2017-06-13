#include "serialportconnectionestablishment.h"

SerialPortConnectionEstablishment::SerialPortConnectionEstablishment(UHV2WorkerVarSet *VarSet)
    : VarSetPtr(VarSet)
{
    anDebug("=> Construct A New State !");
}

SerialPortConnectionEstablishment::~SerialPortConnectionEstablishment()
{
    VarSetPtr = Q_NULLPTR;
    delete VarSetPtr;
}

void SerialPortConnectionEstablishment::onEntry(QEvent *)
{
    anDebug("=> Enter State ...");
    VarSetPtr->SerialPort = new QSerialPort();
    VarSetPtr->configSerialPort();
    if (VarSetPtr->SerialPort->open(QIODevice::ReadWrite))
    {
        anDebug("=> Successfully Open A Serial Port !");
        emit VarSetPtr->Out(QVariant::fromValue(UHV2WorkerVarSet::SerialPortConnect));
        emit VarSetPtr->DirectStateTransitionRequest("SolitaryMessageTransmission");
    }
    else
    {
        anDebug("=> Failed To Open A Serial Port !");
    }
}
