#ifndef UHV2WORKERVARSET_H
#define UHV2WORKERVARSET_H

#include <QObject>
#include <QPair>
#include <QMap>
#include <QSerialPort>
#include "anqtdebug.h"

class UHV2WorkerVarSet: public QObject
{
    Q_OBJECT
public:
    explicit UHV2WorkerVarSet(QObject * parent = Q_NULLPTR);
    ~UHV2WorkerVarSet();
    enum MessageTopic {
        Nothing = 0,
        PortNameRequest,
        PortNameReply,
        UHV2PrioritizedCommandMessage,
        SerialPortError,
        RestartSerialPort,
    };
    Q_ENUM(MessageTopic)
    typedef QPair<QByteArray*,QString*> CommandMessage;
    typedef QPair<qint8,CommandMessage*> PrioritizedCommandMessage;

    QString * PortName = Q_NULLPTR;
    QSerialPort * SerialPort = Q_NULLPTR;
    QMap<qint8,QList<CommandMessage*>*> * PendingMessageList = Q_NULLPTR;
    qint8 lastTransmittedMessagePriority = 0;
    CommandMessage * lastTransmittedMessage = Q_NULLPTR;
    CommandMessage * lastReceivedMessage = Q_NULLPTR;
    void configSerialPort();
signals:
    void DirectStateTransitionRequest(const QString &);
    void PortNameChanged();
    void RestartSerialPortConnection();
    void Out(QVariant, QVariant * = Q_NULLPTR);
};
Q_DECLARE_METATYPE(UHV2WorkerVarSet::PrioritizedCommandMessage)
#endif // UHV2WORKERVARSET_H
