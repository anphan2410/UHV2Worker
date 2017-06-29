#include "serialportinforequest.h"

SerialPortInfoRequest::SerialPortInfoRequest(UHV2WorkerVarSet *VarSet, quint32 TimerIntervalInMilisecond) :
    TimerIntervalMSecs(TimerIntervalInMilisecond)
{
    anDebug("=> Construct A New State !");
    if (TimerIntervalInMilisecond > 0)
    {
        timer.setParent(this);
        timer.setInterval(TimerIntervalInMilisecond);
        QObject::connect(&timer, &QTimer::timeout
                        , this
                        , [VarSet](){
                                anDebug("=> Emit UHV2WorkerVarSet::ANewPortName!");
                                emit VarSet->Out(new QVariant(QVariant::fromValue(UHV2WorkerVarSet::ANewPortName)));
                            }
                        , static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection));
    }
}

void SerialPortInfoRequest::onEntry(QEvent *)
{
    anDebug("=> Enter State ...");
    if (TimerIntervalMSecs > 0)
        timer.start();
}

void SerialPortInfoRequest::onExit(QEvent *)
{
    if (TimerIntervalMSecs > 0)
        timer.stop();
}
