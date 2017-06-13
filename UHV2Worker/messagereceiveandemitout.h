#ifndef MESSAGERECEIVEANDEMITOUT_H
#define MESSAGERECEIVEANDEMITOUT_H

#include <QState>
#include "anqtdebug.h"
#include "uhv2workervarset.h"

class MessageReceiveAndEmitOut : public QState
{
public:
    MessageReceiveAndEmitOut(UHV2WorkerVarSet *VarSet, quint16 ReadTimeOutInMilisecond = 300);
    ~MessageReceiveAndEmitOut();
protected:
    void onEntry(QEvent *) override;
private:    
    UHV2WorkerVarSet * VarSetPtr = Q_NULLPTR;
    quint16 TimeOut4ReadInMilisecond = 0;
};

#endif // MESSAGERECEIVEANDEMITOUT_H
