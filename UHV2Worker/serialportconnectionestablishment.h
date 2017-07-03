#ifndef SERIALPORTCONNECTIONESTABLISHMENT_H
#define SERIALPORTCONNECTIONESTABLISHMENT_H

#include <QState>
#include <QSerialPort>
#include "anlogger.h"
#include "uhv2workervarset.h"

class SerialPortConnectionEstablishment : public QState
{
public:
    SerialPortConnectionEstablishment(UHV2WorkerVarSet * VarSet);
    ~SerialPortConnectionEstablishment();
protected:
    void onEntry(QEvent *) override;
private:
    UHV2WorkerVarSet *VarSetPtr = Q_NULLPTR;
};

#endif // SERIALPORTCONNECTIONESTABLISHMENT_H
