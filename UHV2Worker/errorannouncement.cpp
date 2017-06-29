#include "errorannouncement.h"

ErrorAnnouncement::ErrorAnnouncement(UHV2WorkerVarSet *VarSet, quint32 TimerIntervalInMilisecond)
    : VarSetPtr(VarSet)
{
    anDebug("=> Construct A New State !");
    timer.setParent(this);
    timer.setInterval(TimerIntervalInMilisecond);
    if (VarSet)
    {
        QObject::connect(&timer, &QTimer::timeout
                        , this
                        , [VarSet](){
                                anDebug("=> Emit Error Status!");
                                emit VarSet->Out(new QVariant(QVariant::fromValue(VarSet->ErrorStatus)));
                            }
                        , static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection));
    }
}

void ErrorAnnouncement::onEntry(QEvent *)
{
    timer.start();
}

void ErrorAnnouncement::onExit(QEvent *)
{
    timer.stop();
    VarSetPtr->ErrorStatus = UHV2WorkerVarSet::Nothing;
}
