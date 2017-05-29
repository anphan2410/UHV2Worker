#include "serialportinfovalidation.h"

SerialPortInfoValidation::SerialPortInfoValidation(UHV2Worker *parent)
    : QState(parent), parentPtr(parent)
{

}

SerialPortInfoValidation::~SerialPortInfoValidation()
{
    parentPtr = Q_NULLPTR;
    delete parentPtr;
}

void SerialPortInfoValidation::onEntry(QEvent *)
{
    QSerialPortInfo SerialPortInfo(parentPtr->getPortName());
    if (SerialPortInfo.isNull())
        machine()->postEvent(UHV2Worker::DirectStateTransitionRequest("SerialPortInfoRequest"));
    else
        machine()->postEvent(UHV2Worker::DirectStateTransitionRequest("SerialPortConnectionEstablishment"));
}
