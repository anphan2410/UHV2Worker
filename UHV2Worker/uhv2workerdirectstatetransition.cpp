#include "uhv2workerdirectstatetransition.h"

UHV2WorkerDirectStateTransition::UHV2WorkerDirectStateTransition(UHV2WorkerVarSet *Sender, QAbstractState *destinationState)
    : QSignalTransition(Sender, &UHV2WorkerVarSet::DirectStateTransitionRequest)
{
    this->setTargetState(destinationState);
}

bool UHV2WorkerDirectStateTransition::eventTest(QEvent *e)
{
    if (!(QSignalTransition::eventTest(e) && this->targetState()))
        return false;
    QStateMachine::SignalEvent * se = static_cast<QStateMachine::SignalEvent *>(e);
    return (se->arguments().at(0).toString() == this->targetState()->objectName());
}
