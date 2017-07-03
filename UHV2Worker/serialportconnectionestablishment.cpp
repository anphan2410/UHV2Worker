#include "serialportconnectionestablishment.h"

SerialPortConnectionEstablishment::SerialPortConnectionEstablishment(UHV2WorkerVarSet *VarSet)
    : VarSetPtr(VarSet)
{
    anAck("Construct A New State !");
}

SerialPortConnectionEstablishment::~SerialPortConnectionEstablishment()
{
    VarSetPtr = Q_NULLPTR;
    delete VarSetPtr;
}

void SerialPortConnectionEstablishment::onEntry(QEvent *)
{
    anAck("Enter State ...");
    VarSetPtr->SerialPort = new QSerialPort();
    VarSetPtr->configSerialPort();
    if (VarSetPtr->SerialPort->open(QIODevice::ReadWrite))
    {
        anAck("Successfully Open A Serial Port !");
        emit VarSetPtr->Out(new QVariant(QVariant::fromValue(UHV2WorkerVarSet::SerialPortConnect)));
        emit VarSetPtr->DirectStateTransitionRequest("SolitaryMessageTransmission");
    }
    else
    {
        anAck("Failed To Open A Serial Port !");
    }
}
