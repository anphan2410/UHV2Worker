#ifndef UHV2WORKER_H
#define UHV2WORKER_H

#include <QStateMachine>

class UHV2Worker : public QStateMachine
{
    Q_OBJECT
    Q_ENUMS(DataExchange)
    Q_PROPERTY(QString PortName READ getPortName WRITE setPortName NOTIFY PortNameChanged)
public:
    enum DataExchange {
        PortNameRequest,
        PortNameReply
    };
    UHV2Worker();

    const QString getPortName() const { return *PortName;}

    void setPortName(const QString &NewPortName);
signals:
    void PortNameChanged(const QString &);
    void Out(const DataExchange &, const QVariant * const = Q_NULLPTR);
public slots:
private:
    const QString * PortName = new QString("");

};

Q_DECLARE_METATYPE(UHV2Worker::DataExchange)

#endif // UHV2WORKER_H
