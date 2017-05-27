#ifndef PORTNAMEREQUEST_H
#define PORTNAMEREQUEST_H

#include <QState>
#include <QTimer>
#include "uhv2worker.h"

class PortNameRequest : public QState
{
public:
    PortNameRequest(UHV2Worker *parent, quint32 TimerIntervalInMilisecond = 1000);
protected:
    void onEntry(QEvent *) override;
    void onExit(QEvent *) override;
private:
    QTimer *timer = Q_NULLPTR;
};

#endif // PORTNAMEREQUEST_H
