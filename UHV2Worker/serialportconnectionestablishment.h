#ifndef SERIALPORTCONNECTIONESTABLISHMENT_H
#define SERIALPORTCONNECTIONESTABLISHMENT_H

#include <QState>
#include <QSerialPort>
#include "uhv2worker.h"

class SerialPortConnectionEstablishment : public QState
{
public:
    SerialPortConnectionEstablishment(UHV2Worker::InteractionSet *VarSet);
    ~SerialPortConnectionEstablishment();
protected:
    void onEntry(QEvent *) override;
private:
    UHV2Worker::InteractionSet *VarSetPtr = Q_NULLPTR;
};

#endif // SERIALPORTCONNECTIONESTABLISHMENT_H
