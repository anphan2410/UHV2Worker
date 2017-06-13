#include "solitarymessagetransmission.h"

SolitaryMessageTransmission::SolitaryMessageTransmission(UHV2WorkerVarSet *VarSet, quint16 WriteTimeOutInMilisecond)
    : VarSetPtr(VarSet), TimeOut4WriteInMilisecond(WriteTimeOutInMilisecond)
{
    anDebug("=> Construct A New State !");
}

SolitaryMessageTransmission::~SolitaryMessageTransmission()
{
    VarSetPtr = Q_NULLPTR;
    delete VarSetPtr;
}

void SolitaryMessageTransmission::onEntry(QEvent *)
{
    anDebug("=> Enter State ...");
    if (VarSetPtr->PendingMessageList->size())
    {
        if (VarSetPtr->PendingMessageList->last()->size())
        {
            VarSetPtr->lastTransmittedMessagePriority = VarSetPtr->PendingMessageList->lastKey();
            VarSetPtr->lastTransmittedMessage = VarSetPtr->PendingMessageList->last()->takeFirst();
            if (VarSetPtr->lastTransmittedMessage)
            {
                VarSetPtr->SerialPort->write(*(VarSetPtr->lastTransmittedMessage->first));
                if (VarSetPtr->SerialPort->waitForBytesWritten(TimeOut4WriteInMilisecond))
                {
                    anDebug("=> Successfully Write Message !");
                }
                else
                {
                    anDebug("=> Writing Message Timed Out !");
                    VarSetPtr->lastTransmittedMessage = Q_NULLPTR;
                    emit VarSetPtr->Out(UHV2WorkerVarSet::MessageSendTimedOut);
                }
                emit VarSetPtr->DirectStateTransitionRequest("MessageReceiveAndEmitOut");
            }
        }
    }
}
