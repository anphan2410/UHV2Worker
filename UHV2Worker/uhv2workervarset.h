#ifndef UHV2WORKERVARSET_H
#define UHV2WORKERVARSET_H

#include "uhv2worker.h"
#include <QObject>

class UHV2WorkerVarSet: public QObject
{
    Q_OBJECT
public:
    explicit UHV2WorkerVarSet(QObject *parent = 0);
    QString * PortName = Q_NULLPTR;
    QSerialPort * SerialPort = Q_NULLPTR;
    UHV2Worker::ErrorAndNotification ErrorStatus = Nothing;
    QMap<quint8,QList<QPair<QByteArray*,QString*>*>*> * PendingMessageList = Q_NULLPTR;
signals:
    void PortNameChanged();
    void ErrorStatusSet();
};

#endif // UHV2WORKERVARSET_H
