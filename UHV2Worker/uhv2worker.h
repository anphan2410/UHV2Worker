#ifndef UHV2WORKER_H
#define UHV2WORKER_H

#include <QStateMachine>
#include <QHash>
#include "straystuffs.h"

class UHV2Worker : public QStateMachine
{
    Q_OBJECT
    Q_ENUMS(DataExchange)
    Q_PROPERTY(QString PortName READ getPortName WRITE setPortName NOTIFY PortNameChanged)
public:
    UHV2Worker();
    enum DataExchange {
        PortNameRequest,
        PortNameReply
    };    
    static QEvent *DirectStateTransitionRequest(const QString &StateName);
    static quint16 getStateUserEventNumberByStateName(const QString &StateName);
    static QString *getStateNameByStateUserEventNumber(quint16 StateUserEventNumber);


    const QString getPortName() const { return *PortName;}

    void setPortName(const QString &NewPortName);
signals:
    void PortNameChanged(const QString &);
    void Out(const DataExchange &, const QVariant * const = Q_NULLPTR);
public slots:
private:
    static const QHash<QString, quint16> StateName2StateUserEventNumber;
    static const QHash<quint16, QString> StateUserEventNumber2StateName;
    const QString * PortName = new QString("");

};

Q_DECLARE_METATYPE(UHV2Worker::DataExchange)

#endif // UHV2WORKER_H
