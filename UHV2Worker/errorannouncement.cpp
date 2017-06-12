#include "errorannouncement.h"

ErrorAnnouncement::ErrorAnnouncement(UHV2WorkerVarSet *VarSet, quint32 TimerIntervalInMilisecond)
{
    anDebug("=> Construct A New State !");
    timer.setParent(this);
    timer.setInterval(TimerIntervalInMilisecond);
    if (VarSet)
    {
        QObject::connect(&timer, &QTimer::timeout
                        , this
                        , [VarSet](){
                                anDebug("=> Emit UHV2WorkerVarSet::SerialPortError!");
                                emit VarSet->Out(UHV2WorkerVarSet::SerialPortError);
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
