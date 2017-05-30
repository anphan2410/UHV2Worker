#ifndef UHV2WORKER_H
#define UHV2WORKER_H

#include <QStateMachine>
#include <QHash>
#include <QPair>
#include <QMap>
#include <QSerialPort>
#include "straystuffs.h"
#include "interactionset.h"

class UHV2Worker : public QStateMachine
{
    Q_OBJECT
    Q_ENUMS(DataExchange)
    Q_ENUMS(ErrorAndNotification)
public:
    UHV2Worker();
    enum DataExchange {
        PortNameRequest,
        PortNameReply
    };    
    enum ErrorAndNotification {
        Nothing = 0,
        SerialPortError
    };
    typedef struct
    {
        quint8 Priority = 0;
        QByteArray * Message;
        QString * TimeStamp;
    } CommandMessage;

    static QEvent *DirectStateTransitionRequest(const QString &StateName);
    static quint16 getStateUserEventNumberByStateName(const QString &StateName);
    static QString *getStateNameByStateUserEventNumber(quint16 StateUserEventNumber);


signals:
    void Out(QVariant AnUHV2EnumValue, QVariant * = Q_NULLPTR);
public slots:
    void In(QVariant AnUHV2EnumValue, QVariant * rawData = Q_NULLPTR);
private:
    static const QHash<QString, quint16> StateName2StateUserEventNumber;
    static const QHash<quint16, QString> StateUserEventNumber2StateName;
    InteractionSet * WorkingInteractionSet = Q_NULLPTR;
};

Q_DECLARE_METATYPE(UHV2Worker::DataExchange)
Q_DECLARE_METATYPE(UHV2Worker::ErrorAndNotification)

#endif // UHV2WORKER_H
