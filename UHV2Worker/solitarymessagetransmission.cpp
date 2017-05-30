#include "solitarymessagetransmission.h"

SolitaryMessageTransmission::SolitaryMessageTransmission(UHV2Worker *parent)
    : QState(parent), parentPtr(parent)
{

}

SolitaryMessageTransmission::~SolitaryMessageTransmission()
{
    parentPtr = Q_NULLPTR;
    delete parentPtr;
}

void SolitaryMessageTransmission::onEntry(QEvent *)
{

}
