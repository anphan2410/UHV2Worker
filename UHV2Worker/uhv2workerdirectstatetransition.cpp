#include "uhv2workerdirectstatetransition.h"

UHV2WorkerDirectStateTransition::UHV2WorkerDirectStateTransition(const QString &StateName)
    : mStateName(&StateName)
{

}

UHV2WorkerDirectStateTransition::~UHV2WorkerDirectStateTransition()
{
    mStateName = Q_NULLPTR;
    delete mStateName;
}

bool UHV2WorkerDirectStateTransition::eventTest(QEvent *e)
{
    return (e->type() == (QEvent::User+UHV2Worker::getStateUserEventNumberByStateName(*mStateName)));
}
