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
    if (VarSetPtr->PendingMessageList->size())
    {
        if (VarSetPtr->PendingMessageList->last()->size())
        {
            VarSetPtr->lastTransmittedMessage = VarSetPtr->PendingMessageList->last()->takeFirst();
            if (VarSetPtr->lastTransmittedMessage)
            {
                VarSetPtr->SerialPort->write(*(VarSetPtr->lastTransmittedMessage->first));
            }
        }
    }
}
