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
        anDebug("=> Successfully Open A Serial Port !");
        emit VarSetPtr->DirectStateTransitionRequest("SolitaryMessageTransmission");
    }
    else
    {
        anDebug("=> Failed To Open A Serial Port !");
    }
}
