#include "serialportinfovalidation.h"

SerialPortInfoValidation::SerialPortInfoValidation(UHV2WorkerVarSet *VarSet)
    : VarSetPtr(VarSet)
{
    anDebug("=> Construct A New State !");
}

SerialPortInfoValidation::~SerialPortInfoValidation()
{
    VarSetPtr = Q_NULLPTR;
    delete VarSetPtr;
}

void SerialPortInfoValidation::onEntry(QEvent *)
{
    anDebug("=> Enter State ...");
    if (VarSetPtr->SerialPort)
    {
        if (VarSetPtr->SerialPort->isOpen())
        {
            VarSetPtr->SerialPort->close();
            anqDebug("=> SerialPort Disconnected !");
        }
        else
        {
            anqDebug("=> SerialPort Already Not Connected !");
        }
    }
    else
    {
        anqDebug("=> SerialPort Already Not Exist !");
    }
    QSerialPortInfo SerialPortInfo(*(VarSetPtr->PortName));
    if (SerialPortInfo.isNull())
    {
        anDebug("=> SerialPortInfo Is Null !");
        emit VarSetPtr->DirectStateTransitionRequest("SerialPortInfoRequest");
    }
    else
    {
        anDebug("=> SerialPortInfo Exists !");
        emit VarSetPtr->DirectStateTransitionRequest("SerialPortConnectionEstablishment");
    }
}
