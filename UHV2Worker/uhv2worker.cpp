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

void UHV2Worker::setPortName(const QString &NewPortName)
{
    PortName = new QString(NewPortName);
    emit PortNameChanged(*PortName);
}

const QHash<QString, quint16> UHV2Worker::StateName2StateUserEventNumber = QHash<QString, quint16>
({
     {"SerialPortInfoRequest",0},
     {"SerialPortInfoValidation",1},
     {"SerialPortConnectionEstablishment",2}

 });

const QHash<quint16, QString> UHV2Worker::StateUserEventNumber2StateName = SwapKeyValOnOneToOneQHash(UHV2Worker::StateName2StateUserEventNumber);
