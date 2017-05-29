#include "uhv2worker.h"

UHV2Worker::UHV2Worker()
{

}

QEvent *UHV2Worker::DirectStateTransitionRequest(const QString &StateName)
{
    return new QEvent(QEvent::Type(QEvent::User+UHV2Worker::StateName2StateUserEventNumber.value(StateName)));
}

quint16 UHV2Worker::getStateUserEventNumberByStateName(const QString &StateName)
{
    return UHV2Worker::StateName2StateUserEventNumber.value(StateName);
}

QString *UHV2Worker::getStateNameByStateUserEventNumber(quint16 StateUserEventNumber)
{
    return new QString(UHV2Worker::StateUserEventNumber2StateName.value(StateUserEventNumber));;
}

const UHV2Worker::ErrorAndNotification UHV2Worker::getErrorStatus() const
{
    return ErrorStatus;
}

void UHV2Worker::setPortName(const QString &NewPortName)
{
    PortName = new QString(NewPortName);
    emit PortNameChanged(*PortName);
}

void UHV2Worker::setSerialPort(QSerialPort *ASerialPort)
{
    SerialPort = ASerialPort;
}

void UHV2Worker::setErrorStatus(UHV2Worker::ErrorAndNotification AnErrorStatus)
{
    ErrorStatus = AnErrorStatus;
    if (ErrorStatus != UHV2Worker::Nothing)
    {
        emit ErrorStatusSet();
    }
}

void UHV2Worker::clearErrorStatus()
{
    ErrorStatus = UHV2Worker::Nothing;
}

const QHash<QString, quint16> UHV2Worker::StateName2StateUserEventNumber = QHash<QString, quint16>
({
     {"SerialPortInfoRequest",0},
     {"SerialPortInfoValidation",1},
     {"SerialPortConnectionEstablishment",2},
     {"SendACommand",3},
     {"ErrorAnnouncement",7}
 });

const QHash<quint16, QString> UHV2Worker::StateUserEventNumber2StateName = SwapKeyValOnOneToOneQHash(UHV2Worker::StateName2StateUserEventNumber);
