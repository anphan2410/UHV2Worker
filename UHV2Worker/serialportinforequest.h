#ifndef SERIALPORTINFOREQUEST_H
#define SERIALPORTINFOREQUEST_H

#include <QState>
#include <QTimer>
#include "uhv2worker.h"

class SerialPortInfoRequest : public QState
{
public:
    SerialPortInfoRequest(UHV2Worker *parent, quint32 TimerIntervalInMilisecond = 1000);
protected:
    void onEntry(QEvent *) override;
    void onExit(QEvent *) override;
private:
    QTimer timer;
};

#endif // SERIALPORTINFOREQUEST_H
