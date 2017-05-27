#include "portnamerequest.h"

PortNameRequest::PortNameRequest(UHV2Worker *parent, quint32 TimerIntervalInMilisecond)
    : QState(parent)
{
    timer = new QTimer(this);
    timer->setInterval(TimerIntervalInMilisecond);
    if (parent)
    {
        QObject::connect(timer, &QTimer::timeout
                        , [parent](){
                                emit parent->Out(UHV2Worker::PortNameRequest);
                            });
https://stackoverflow.com/questions/26246940/when-should-i-provide-a-destructor-for-my-class
https://wiki.qt.io/New_Signal_Slot_Syntax#Overload
    }
}

void PortNameRequest::onEntry(QEvent *)
{
    timer->start();
}

void PortNameRequest::onExit(QEvent *)
{
    timer->stop();
}
