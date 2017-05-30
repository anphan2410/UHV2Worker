#include "uhv2worker.h"

UHV2Worker::UHV2Worker()
{

    qRegisterMetaType<UHV2Worker::DataExchange>("UHV2Worker::DataExchange");
    qRegisterMetaType<UHV2Worker::ErrorAndNotification>("UHV2Worker::ErrorAndNotification");
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

void UHV2Worker::In(QVariant AnUHV2EnumValue, QVariant *rawData)
{
    switch (AnUHV2EnumValue.toInt()) {
    case PortNameReply:
        if (rawData->toString() != "")
        {
            *(WorkingInteractionSet->PortName) = rawData->toString();
            emit WorkingInteractionSet->PortNameChanged();
        }
        break;
    default:
        break;
    }
}

//void UHV2Worker::setSerialPort(QSerialPort *ASerialPort)
//{
//    SerialPort = ASerialPort;
//    QObject::connect(SerialPort,&QSerialPort::errorOccurred
//                     ,this,[this]()
//                            {
//                                this->setErrorStatus(UHV2Worker::SerialPortError);
//                            });
//}

//void UHV2Worker::setErrorStatus(UHV2Worker::ErrorAndNotification AnErrorStatus)
//{
//    ErrorStatus = AnErrorStatus;
//    if (ErrorStatus != UHV2Worker::Nothing)
//    {
//        emit ErrorStatusSet();
//    }
//}

const QHash<QString, quint16> UHV2Worker::StateName2StateUserEventNumber = QHash<QString, quint16>
({
     {"SerialPortInfoRequest",0},
     {"SerialPortInfoValidation",1},
     {"SerialPortConnectionEstablishment",2},
     {"SolitaryMessageTransmission",3},
     {"ErrorAnnouncement",7}
 });

const QHash<quint16, QString> UHV2Worker::StateUserEventNumber2StateName = SwapKeyValOnOneToOneQHash(UHV2Worker::StateName2StateUserEventNumber);
