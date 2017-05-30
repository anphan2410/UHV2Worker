#include "serialportinforequest.h"

SerialPortInfoRequest::SerialPortInfoRequest(UHV2Worker *parent, quint32 TimerIntervalInMilisecond)
{
    timer.setParent(this);
    timer.setInterval(TimerIntervalInMilisecond);
    if (parent)
    {
        QObject::connect(&timer, &QTimer::timeout
                        , this
                        , [parent](){
                                emit parent->Out(UHV2Worker::PortNameRequest);
                            }
                        , static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection));
    }
}

void SerialPortInfoRequest::onEntry(QEvent *)
{
    timer.start();
}

void SerialPortInfoRequest::onExit(QEvent *)
{
    timer.stop();
}
