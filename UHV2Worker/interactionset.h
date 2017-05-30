#ifndef INTERACTIONSET_H
#define INTERACTIONSET_H

#include "uhv2worker.h"
#include <QObject>

class InteractionSet : public QObject
{
    Q_OBJECT
public:
    explicit InteractionSet(QObject *parent = 0);
    QString * PortName = Q_NULLPTR;
    QSerialPort * SerialPort = Q_NULLPTR;
    UHV2Worker::ErrorAndNotification ErrorStatus = Nothing;
    QMap<quint8,QList<QPair<QByteArray*,QString*>*>*> * PendingMessageList = Q_NULLPTR;
signals:
    void PortNameChanged();
    void ErrorStatusSet();
public slots:
};

#endif // INTERACTIONSET_H
