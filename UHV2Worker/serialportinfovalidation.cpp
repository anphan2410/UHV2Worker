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
    QSerialPortInfo SerialPortInfo(*(VarSetPtr->PortName));
    if (SerialPortInfo.isNull())
    {
        emit VarSetPtr->DirectStateTransitionRequest("SerialPortInfoRequest");
    }
    else
    {
        emit VarSetPtr->DirectStateTransitionRequest("SerialPortConnectionEstablishment");
    }
}
