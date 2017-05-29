#ifndef SERIALPORTCONNECTIONESTABLISHMENT_H
#define SERIALPORTCONNECTIONESTABLISHMENT_H

#include <QState>
#include <QSerialPort>
#include "uhv2worker.h"

class SerialPortConnectionEstablishment : public QState
{
public:
    SerialPortConnectionEstablishment(UHV2Worker *parent);
    ~SerialPortConnectionEstablishment();
protected:
    void onEntry(QEvent *) override;
private:
    quint8 failTimeCount = 0;
    UHV2Worker *parentPtr = Q_NULLPTR;
};

#endif // SERIALPORTCONNECTIONESTABLISHMENT_H
