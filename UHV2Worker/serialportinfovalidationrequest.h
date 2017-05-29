#ifndef SERIALPORTINFOVALIDATIONREQUEST_H
#define SERIALPORTINFOVALIDATIONREQUEST_H

#include <QSignalTransition>
#include "uhv2worker.h"

class SerialPortInfoValidationRequest : public QSignalTransition
{
public:
    SerialPortInfoValidationRequest(UHV2Worker *parent);
    bool eventTest(QEvent *e) override;
};

#endif // SERIALPORTINFOVALIDATIONREQUEST_H
