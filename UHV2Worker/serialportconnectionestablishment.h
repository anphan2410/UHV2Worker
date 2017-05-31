#ifndef SERIALPORTCONNECTIONESTABLISHMENT_H
#define SERIALPORTCONNECTIONESTABLISHMENT_H

#include <QState>
#include <QSerialPort>
#include "uhv2worker.h"

class SerialPortConnectionEstablishment : public QState
{
public:
    SerialPortConnectionEstablishment(UHV2Worker * parent, UHV2WorkerVarSet * VarSet);
    ~SerialPortConnectionEstablishment();
protected:
    void onEntry(QEvent *) override;
private:
    UHV2Worker * parentPtr = Q_NULLPTR;
    UHV2WorkerVarSet *VarSetPtr = Q_NULLPTR;
};

#endif // SERIALPORTCONNECTIONESTABLISHMENT_H
