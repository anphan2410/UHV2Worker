#include "serialportinfovalidation.h"

SerialPortInfoValidation::SerialPortInfoValidation(UHV2WorkerVarSet *VarSet)
    : VarSetPtr(VarSet)
{
    anAck("Construct A New State !");
}

SerialPortInfoValidation::~SerialPortInfoValidation()
{
    VarSetPtr = Q_NULLPTR;
    delete VarSetPtr;
}

void SerialPortInfoValidation::onEntry(QEvent *)
{
    anAck("Enter State ...");
    if (VarSetPtr->SerialPort)
    {
        if (VarSetPtr->SerialPort->isOpen())
        {
            VarSetPtr->SerialPort->close();
            anInfo("SerialPort Disconnected !");
        }
        else
        {
            anInfo("SerialPort Already Not Connected !");
        }
    }
    else
    {
        anInfo("SerialPort Already Not Exist !");
    }
    QSerialPortInfo SerialPortInfo(*(VarSetPtr->PortName));
    if (SerialPortInfo.isNull())
    {
        anWarn("SerialPortInfo Is Null !");
        emit VarSetPtr->DirectStateTransitionRequest("SerialPortInfoRequest");
    }
    else
    {
        anAck("SerialPortInfo Exists !");
        emit VarSetPtr->DirectStateTransitionRequest("SerialPortConnectionEstablishment");
    }
}
