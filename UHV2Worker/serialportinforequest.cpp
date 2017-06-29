#include "serialportinforequest.h"

SerialPortInfoRequest::SerialPortInfoRequest(UHV2WorkerVarSet *VarSet, quint32 TimerIntervalInMilisecond)
{
    anDebug("=> Construct A New State !");
    timer.setParent(this);
    timer.setInterval(TimerIntervalInMilisecond);
    if (VarSet)
    {
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
    timer.start();
}

void SerialPortInfoRequest::onExit(QEvent *)
{
    timer.stop();
}
