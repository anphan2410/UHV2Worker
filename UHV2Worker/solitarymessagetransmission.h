#ifndef SOLITARYMESSAGETRANSMISSION_H
#define SOLITARYMESSAGETRANSMISSION_H

#include <QState>
#include "uhv2worker.h"

class SolitaryMessageTransmission : public QState
{
public:
    SolitaryMessageTransmission(UHV2Worker *parent, UHV2WorkerVarSet *VarSet);
    ~SolitaryMessageTransmission();
protected:
    void onEntry(QEvent *) override;
private:
    UHV2Worker * parentPtr = Q_NULLPTR;
    UHV2WorkerVarSet * VarSetPtr = Q_NULLPTR;
};

#endif // SOLITARYMESSAGETRANSMISSION_H
