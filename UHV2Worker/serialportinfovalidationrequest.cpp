#include "serialportinfovalidationrequest.h"

SerialPortInfoValidationRequest::SerialPortInfoValidationRequest(UHV2Worker *parent)
    : QSignalTransition(parent, &UHV2Worker::PortNameChanged)
{

}

bool SerialPortInfoValidationRequest::eventTest(QEvent *e)
{
    if (!QSignalTransition::eventTest(e))
        return false;
    QStateMachine::SignalEvent *se = static_cast<QStateMachine::SignalEvent*>(e);
    return (se->arguments().at(0).toString() != "");
}
