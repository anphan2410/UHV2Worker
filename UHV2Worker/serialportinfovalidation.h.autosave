#ifndef SERIALPORTINFOVALIDATION_H
#define SERIALPORTINFOVALIDATION_H

#include <QState>
#include <QSerialPortInfo>
#include "anqtdebug.h"
#include "uhv2workervarset.h"

class SerialPortInfoValidation : public QState
{
public:
    SerialPortInfoValidation(UHV2WorkerVarSet *VarSet);
    ~SerialPortInfoValidation();
protected:
    void onEntry(QEvent *) override;
private:
    UHV2WorkerVarSet *VarSetPtr = Q_NULLPTR;
};

#endif // SERIALPORTINFOVALIDATION_H
