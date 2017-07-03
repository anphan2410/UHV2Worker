#ifndef SOLITARYMESSAGETRANSMISSION_H
#define SOLITARYMESSAGETRANSMISSION_H

#include <QState>
#include "anlogger.h"
#include "uhv2workervarset.h"

class SolitaryMessageTransmission : public QState
{
public:
    SolitaryMessageTransmission(UHV2WorkerVarSet *VarSet, quint16 WriteTimeOutInMilisecond = 100);
    ~SolitaryMessageTransmission();
protected:
    void onEntry(QEvent *) override;
private:
    UHV2WorkerVarSet * VarSetPtr = Q_NULLPTR;    
    quint16 TimeOut4WriteInMilisecond = 0;
};

#endif // SOLITARYMESSAGETRANSMISSION_H
