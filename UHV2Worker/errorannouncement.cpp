#include "errorannouncement.h"

ErrorAnnouncement::ErrorAnnouncement(UHV2WorkerVarSet *VarSet, quint32 TimerIntervalInMilisecond)
    : VarSetPtr(VarSet), TimerIntervalMSecs(TimerIntervalInMilisecond)
{
    anAck("Construct A New State !");
    if (TimerIntervalInMilisecond > 0)
    {
        timer.setParent(this);
        timer.setInterval(TimerIntervalInMilisecond);
        QObject::connect(&timer, &QTimer::timeout
                        , this
                        , [VarSet](){
                                anWarn("Emit Error Status!");
                                emit VarSet->Out(new QVariant(QVariant::fromValue(VarSet->ErrorStatus)));
                            }
                        , static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection));
    }
}

void ErrorAnnouncement::onEntry(QEvent *)
{
    anAck("Enter State ...");
    if (TimerIntervalMSecs > 0)
        timer.start();
}

void ErrorAnnouncement::onExit(QEvent *)
{
    if (TimerIntervalMSecs > 0)
        timer.stop();
    VarSetPtr->ErrorStatus = UHV2WorkerVarSet::Nothing;
}
