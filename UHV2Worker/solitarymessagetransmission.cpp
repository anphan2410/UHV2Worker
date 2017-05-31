#include "solitarymessagetransmission.h"

SolitaryMessageTransmission::SolitaryMessageTransmission(UHV2Worker *parent, UHV2WorkerVarSet *VarSet)
    : QState(parent), parentPtr(parent), VarSetPtr(VarSet)
{

}

SolitaryMessageTransmission::~SolitaryMessageTransmission()
{
    parentPtr = Q_NULLPTR;
    VarSetPtr = Q_NULLPTR;
    delete parentPtr;
    delete VarSetPtr;
}

void SolitaryMessageTransmission::onEntry(QEvent *)
{
    if (VarSetPtr->currentReceivedMessage)
    {
        VarSetPtr->currentReceivedMessage->first = Q_NULLPTR;
        VarSetPtr->currentReceivedMessage->second = Q_NULLPTR;
        VarSetPtr->currentReceivedMessage = Q_NULLPTR;
    }
    if (VarSetPtr->PendingMessageList->size())
    {
        if (VarSetPtr->PendingMessageList->last()->size())
        {
            VarSetPtr->currentTransmittedMessage = VarSetPtr->PendingMessageList->last()->takeFirst();
            if (VarSetPtr->currentTransmittedMessage)
            {
                VarSetPtr->SerialPort->write(*(VarSetPtr->currentTransmittedMessage->first));
            }
        }
    }
}
