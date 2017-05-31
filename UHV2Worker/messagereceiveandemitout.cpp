#include "messagereceiveandemitout.h"

MessageReceiveAndEmitOut::MessageReceiveAndEmitOut(UHV2Worker *parent, UHV2WorkerVarSet *VarSet, quint16 ReadTimeOutInMilisecond)
    : QState(parent), parentPtr(parent), VarSetPtr(VarSet), TimeOut4ReadInMilisecond(ReadTimeOutInMilisecond)
{

}

MessageReceiveAndEmitOut::~MessageReceiveAndEmitOut()
{
    UniKey = Q_NULLPTR;
    parentPtr = Q_NULLPTR;
    VarSetPtr = Q_NULLPTR;
    delete UniKey;
    delete parentPtr;
    delete VarSetPtr;
}

void MessageReceiveAndEmitOut::onEntry(QEvent *)
{
    if (VarSetPtr->currentTransmittedMessage)
    {
        UniKey = VarSetPtr->currentTransmittedMessage->second;
        VarSetPtr->currentTransmittedMessage->first = Q_NULLPTR;
        VarSetPtr->currentTransmittedMessage->second = Q_NULLPTR;
        VarSetPtr->currentTransmittedMessage = Q_NULLPTR;
        VarSetPtr->lastTransmittedMessagePriority = 0;
    }
    if (VarSetPtr->SerialPort->waitForReadyRead(TimeOut4ReadInMilisecond*10))
    {
        QByteArray tmpRead(VarSetPtr->SerialPort->readAll());
        while (VarSetPtr->SerialPort->waitForReadyRead(TimeOut4ReadInMilisecond))
        {
            tmpRead+=VarSetPtr->SerialPort->readAll();
        }
        VarSetPtr->currentReceivedMessage = new UHV2WorkerVarSet::CommandMessage();
        VarSetPtr->currentReceivedMessage->first = new QByteArray(tmpRead);
        VarSetPtr->currentReceivedMessage->second = UniKey;
        UniKey = Q_NULLPTR;
        emit parentPtr->Out();
    }
}
