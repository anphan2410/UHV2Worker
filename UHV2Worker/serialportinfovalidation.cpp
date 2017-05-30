#include "serialportinfovalidation.h"

SerialPortInfoValidation::SerialPortInfoValidation(UHV2Worker::InteractionSet *VarSet)
    : VarSetPtr(VarSet)
{

}

SerialPortInfoValidation::~SerialPortInfoValidation()
{
    VarSetPtr = Q_NULLPTR;
    delete VarSetPtr;
}

void SerialPortInfoValidation::onEntry(QEvent *)
{
    QSerialPortInfo SerialPortInfo(*VarSetPtr->PortName);
    if (SerialPortInfo.isNull())
        machine()->postEvent(UHV2Worker::DirectStateTransitionRequest("SerialPortInfoRequest"));
    else
    {
        machine()->postEvent(UHV2Worker::DirectStateTransitionRequest("SerialPortConnectionEstablishment"));
    }
}
