#ifndef UHV2WORKERDIRECTSTATETRANSITION_H
#define UHV2WORKERDIRECTSTATETRANSITION_H

#include <QAbstractTransition>
#include "uhv2worker.h"

class UHV2WorkerDirectStateTransition : public QAbstractTransition
{
public:
    UHV2WorkerDirectStateTransition(const QString &StateName);
protected:
    virtual bool eventTest(QEvent *e) override;
private:
    const QString mStateName;
};

#endif // UHV2WORKERDIRECTSTATETRANSITION_H
