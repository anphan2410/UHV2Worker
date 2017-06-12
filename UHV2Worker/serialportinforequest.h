#ifndef SERIALPORTINFOREQUEST_H
#define SERIALPORTINFOREQUEST_H

#include <QState>
#include <QTimer>
#include "anqtdebug.h"
#include "uhv2workervarset.h"

class SerialPortInfoRequest : public QState
{
public:
    SerialPortInfoRequest(UHV2WorkerVarSet *VarSet, quint32 TimerIntervalInMilisecond = 1000);
protected:
    void onEntry(QEvent *) override;
    void onExit(QEvent *) override;
private:
    QTimer timer;
};

#endif // SERIALPORTINFOREQUEST_H
