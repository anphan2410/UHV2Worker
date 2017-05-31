#ifndef UHV2WORKERDIRECTSTATETRANSITION_H
#define UHV2WORKERDIRECTSTATETRANSITION_H

#include <QSignalTransition>
#include <QAbstractState>
#include "uhv2worker.h"

class UHV2WorkerDirectStateTransition : public QSignalTransition
{
public:
    UHV2WorkerDirectStateTransition(UHV2Worker *Sender, QAbstractState *destinationState);
protected:
    virtual bool eventTest(QEvent *e) override;
};

#endif // UHV2WORKERDIRECTSTATETRANSITION_H
