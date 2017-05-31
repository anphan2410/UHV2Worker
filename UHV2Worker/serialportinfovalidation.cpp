#include "serialportinfovalidation.h"

SerialPortInfoValidation::SerialPortInfoValidation(UHV2Worker *parent, UHV2WorkerVarSet *VarSet)
    : QState(parent), parentPtr(parent), VarSetPtr(VarSet)
{

}

SerialPortInfoValidation::~SerialPortInfoValidation()
{
    parentPtr = Q_NULLPTR;
    VarSetPtr = Q_NULLPTR;
    delete parentPtr;
    delete VarSetPtr;
}

void SerialPortInfoValidation::onEntry(QEvent *)
{
    QSerialPortInfo SerialPortInfo(*(VarSetPtr->PortName));
    if (SerialPortInfo.isNull())
    {
        emit parentPtr->DirectStateTransitionRequest("SerialPortInfoRequest");
    }
    else
    {
        emit parentPtr->DirectStateTransitionRequest("SerialPortConnectionEstablishment");
    }
}
