#ifndef ERRORANNOUNCEMENT_H
#define ERRORANNOUNCEMENT_H

#include <QState>
#include <QTimer>
#include "anqtdebug.h"
#include "uhv2workervarset.h"

class ErrorAnnouncement : public QState
{
public:
    ErrorAnnouncement(UHV2WorkerVarSet *VarSet, quint32 TimerIntervalInMilisecond = 1000);
protected:
    void onEntry(QEvent *) override;
    void onExit(QEvent *) override;
private:
    QTimer timer;
    UHV2WorkerVarSet * VarSetPtr = Q_NULLPTR;
};

#endif // ERRORANNOUNCEMENT_H
