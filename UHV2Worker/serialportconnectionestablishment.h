#ifndef SERIALPORTCONNECTIONESTABLISHMENT_H
#define SERIALPORTCONNECTIONESTABLISHMENT_H

#include <QState>
#include <QSerialPort>
#include "uhv2worker.h"

class SerialPortConnectionEstablishment : public QState
{
public:
    SerialPortConnectionEstablishment();
};

#endif // SERIALPORTCONNECTIONESTABLISHMENT_H
