#ifndef UHV2WORKER_H
#define UHV2WORKER_H

#include <QStateMachine>
#include <QHash>
#include <QPair>
#include <QMap>
#include <QSerialPort>
#include "uhv2workervarset.h"
#include "straystuffs.h"

class UHV2Worker : public QStateMachine
{
    Q_OBJECT
public:
    UHV2Worker();
signals:
    void DirectStateTransitionRequest(const QString &);
    void Out(QVariant AnUHV2EnumValue, QVariant * = Q_NULLPTR);
public slots:
    void In(QVariant AnUHV2EnumValue, QVariant * rawData = Q_NULLPTR);
private:
    UHV2WorkerVarSet * WorkingVarSet = Q_NULLPTR;
};

#endif // UHV2WORKER_H
