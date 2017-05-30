#include "serialportconnectionestablishment.h"

SerialPortConnectionEstablishment::SerialPortConnectionEstablishment(UHV2Worker::InteractionSet *VarSet)
    : VarSetPtr(VarSet)
{

}

SerialPortConnectionEstablishment::~SerialPortConnectionEstablishment()
{
    VarSetPtr = Q_NULLPTR;
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
    VarSetPtr->SerialPort = new QSerialPort(*VarSetPtr->PortName);
    if (VarSetPtr->SerialPort->open(QIODevice::ReadWrite))
    {
        machine()->postEvent(UHV2Worker::DirectStateTransitionRequest("SolitaryMessageTransmission"));
    }
}
