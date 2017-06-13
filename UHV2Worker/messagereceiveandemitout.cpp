#include "messagereceiveandemitout.h"

MessageReceiveAndEmitOut::MessageReceiveAndEmitOut(UHV2WorkerVarSet *VarSet, quint16 ReadTimeOutInMilisecond)
    : VarSetPtr(VarSet), TimeOut4ReadInMilisecond(ReadTimeOutInMilisecond)
{
    anDebug("=> Construct A New State !");
}

MessageReceiveAndEmitOut::~MessageReceiveAndEmitOut()
{
    VarSetPtr = Q_NULLPTR;
    delete VarSetPtr;
}

void MessageReceiveAndEmitOut::onEntry(QEvent *)
{
    anDebug("=> Enter State ...");
    if (VarSetPtr->SerialPort->waitForReadyRead(TimeOut4ReadInMilisecond*10))
    {
        QByteArray tmpRead(VarSetPtr->SerialPort->readAll());
        while (VarSetPtr->SerialPort->waitForReadyRead(TimeOut4ReadInMilisecond))
        {
            tmpRead+=VarSetPtr->SerialPort->readAll();
        }
        VarSetPtr->lastReceivedMessage = new UHV2WorkerVarSet::CommandMessage();
        VarSetPtr->lastReceivedMessage->first = new QByteArray(tmpRead);
        VarSetPtr->lastReceivedMessage->second = VarSetPtr->lastTransmittedMessage->second;
        anDebug("=> Successfully To Read Message !");
        emit VarSetPtr->Out(QVariant::fromValue(UHV2WorkerVarSet::AnUHV2PrioritizedCommandMessage),
                            new QVariant(QVariant::fromValue(UHV2WorkerVarSet::PrioritizedCommandMessage(VarSetPtr->lastTransmittedMessagePriority, VarSetPtr->lastReceivedMessage))));
    }
    else
    {
        anDebug("=> Reading Message Timed Out !");
        VarSetPtr->lastReceivedMessage = Q_NULLPTR;
        emit VarSetPtr->Out(QVariant::fromValue(UHV2WorkerVarSet::MessageReadTimedOut));
    }
    emit VarSetPtr->DirectStateTransitionRequest("SolitaryMessageTransmission");
}
