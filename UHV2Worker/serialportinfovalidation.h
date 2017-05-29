#ifndef SERIALPORTINFOVALIDATION_H
#define SERIALPORTINFOVALIDATION_H

#include <QState>
#include <QSerialPortInfo>
#include "uhv2worker.h"

class SerialPortInfoValidation : public QState
{
public:
    SerialPortInfoValidation(UHV2Worker *parent);
    ~SerialPortInfoValidation();
protected:
    void onEntry(QEvent *) override;
private:
    UHV2Worker *parentPtr;
};

#endif // SERIALPORTINFOVALIDATION_H
