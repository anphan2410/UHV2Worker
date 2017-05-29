#ifndef UHV2WORKER_H
#define UHV2WORKER_H

#include <QStateMachine>
#include <QHash>
#include <QSerialPort>
#include "straystuffs.h"

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
        Nothing,
        SerialPortBusy,
        SerialPortFailedToOpen
    };

    static QEvent *DirectStateTransitionRequest(const QString &StateName);
    static quint16 getStateUserEventNumberByStateName(const QString &StateName);
    static QString *getStateNameByStateUserEventNumber(quint16 StateUserEventNumber);

    const QString getPortName() const { return *PortName;}
    const ErrorAndNotification getErrorStatus() const;


    void setPortName(const QString &NewPortName);

    void setSerialPort(QSerialPort * ASerialPort);

    void setErrorStatus(ErrorAndNotification AnErrorStatus);
    void clearErrorStatus();
signals:
    void PortNameChanged(const QString &);
    void ErrorStatusSet();
    void Out(const DataExchange &, const QVariant * const = Q_NULLPTR);
public slots:
private:
    static const QHash<QString, quint16> StateName2StateUserEventNumber;
    static const QHash<quint16, QString> StateUserEventNumber2StateName;
    QString * PortName = new QString("");
    QSerialPort * SerialPort = Q_NULLPTR;
    ErrorAndNotification ErrorStatus = Nothing;
};

Q_DECLARE_METATYPE(UHV2Worker::DataExchange)
Q_DECLARE_METATYPE(UHV2Worker::ErrorAndNotification)

#endif // UHV2WORKER_H
