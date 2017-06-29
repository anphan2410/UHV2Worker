#ifndef UHV2WORKERVARSET_H
#define UHV2WORKERVARSET_H

#include <QApplication>
#include <QObject>
#include <QPair>
#include <QThread>
#include <QMap>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QStateMachine>
#include <QMetaType>
#include "anqtdebug.h"

class UHV2WorkerVarSet: public QObject
{
    Q_OBJECT
public:
    explicit UHV2WorkerVarSet(QObject * parent = Q_NULLPTR);
    ~UHV2WorkerVarSet();
    enum MessageTopic {
        Nothing = 0,
        ANewPortName,
        AnUHV2PrioritizedCommandMessage,
        SerialPortError,
        SerialPortDisconnect,
        SerialPortConnect,
        SerialPortRestart,
        MessageSendTimedOut,
        MessageReadTimedOut,
        PendingMessageListClear
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
    void initialize();
    MessageTopic ErrorStatus = Nothing;
signals:
    void DirectStateTransitionRequest(const QString &);
    void PortNameChanged();
    void RestartSerialPortConnection();
    void AFirstPrioritizedCommandMessageReceived();
    void Out(QVariant *, QVariant * = Q_NULLPTR);
};
Q_DECLARE_METATYPE(UHV2WorkerVarSet::PrioritizedCommandMessage)
#endif // UHV2WORKERVARSET_H
