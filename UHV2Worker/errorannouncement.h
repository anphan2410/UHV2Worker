#ifndef ERRORANNOUNCEMENT_H
#define ERRORANNOUNCEMENT_H

#include <QState>
#include <QTimer>
#include "anlogger.h"
#include "uhv2workervarset.h"

class ErrorAnnouncement : public QState
{
public:
    ErrorAnnouncement(UHV2WorkerVarSet *VarSet, quint32 TimerIntervalInMilisecond = 0);
protected:
    void onEntry(QEvent *) override;
    void onExit(QEvent *) override;
private:
    QTimer timer;
    UHV2WorkerVarSet * VarSetPtr = Q_NULLPTR;
    quint32 TimerIntervalMSecs = 0;
};

#endif // ERRORANNOUNCEMENT_H
