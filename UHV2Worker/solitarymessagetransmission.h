#ifndef SOLITARYMESSAGETRANSMISSION_H
#define SOLITARYMESSAGETRANSMISSION_H

#include <QState>
#include "anqtdebug.h"
#include "uhv2workervarset.h"

class SolitaryMessageTransmission : public QState
{
public:
    SolitaryMessageTransmission(UHV2WorkerVarSet *VarSet, quint16 WriteTimeOutInMilisecond = 100);
    ~SolitaryMessageTransmission();
protected:
    void onEntry(QEvent *) override;
private:
    quint16 TimeOut4WriteInMilisecond = 0;
    UHV2WorkerVarSet * VarSetPtr = Q_NULLPTR;
};

#endif // SOLITARYMESSAGETRANSMISSION_H
