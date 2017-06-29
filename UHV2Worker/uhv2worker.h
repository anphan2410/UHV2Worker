#ifndef UHV2WORKER_H
#define UHV2WORKER_H

#include <QStateMachine>
#include <QSignalTransition>
#include "uhv2workervarset.h"
#include "anqtdebug.h"
#include "straystuffs.h"
#include "serialportinforequest.h"
#include "serialportinfovalidation.h"
#include "serialportconnectionestablishment.h"
#include "solitarymessagetransmission.h"
#include "messagereceiveandemitout.h"
#include "errorannouncement.h"
#include "uhv2workerdirectstatetransition.h"

class UHV2Worker : public QStateMachine
{
    Q_OBJECT
public:
    UHV2Worker();
signals:    
    void Out(QVariant *, QVariant * = Q_NULLPTR);
public slots:
    void In(QVariant * AnUHV2WorkerEnumValue, QVariant * rawData = Q_NULLPTR);
private:
    UHV2WorkerVarSet * WorkingVarSet = Q_NULLPTR;    
};

#endif // UHV2WORKER_H
