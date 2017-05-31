#ifndef UHV2WORKERVARSET_H
#define UHV2WORKERVARSET_H

#include <QObject>
#include <QSerialPort>

class UHV2WorkerVarSet: public QObject
{
    Q_OBJECT
public:
    explicit UHV2WorkerVarSet(QObject * parent = Q_NULLPTR);
    ~UHV2WorkerVarSet();
    enum DataExchange {
        PortNameRequest,
        PortNameReply
    };
    Q_ENUM(DataExchange)
    enum ErrorAndNotification {
        Nothing = 0,
        SerialPortError,

    };
    Q_ENUM(ErrorAndNotification)
    typedef QPair<QByteArray*,QString*> CommandMessage;
    typedef QPair<qint8,CommandMessage*> PrioritizedCommandMessage;

    QString * PortName = Q_NULLPTR;
    QSerialPort * SerialPort = Q_NULLPTR;
    ErrorAndNotification ErrorStatus = Nothing;
    QMap<qint8,QList<CommandMessage*>*> * PendingMessageList = Q_NULLPTR;
    qint8 lastTransmittedMessagePriority = 0;
    CommandMessage * currentTransmittedMessage = Q_NULLPTR;
    CommandMessage * currentReceivedMessage = Q_NULLPTR;
signals:
    void PortNameChanged();
    void ErrorStatusSet();
public slots:
    void configSerialPort();
};

#endif // UHV2WORKERVARSET_H
