#ifndef MESSAGERECEIVEANDEMITOUT_H
#define MESSAGERECEIVEANDEMITOUT_H

#include <QState>
#include "uhv2worker.h"

class MessageReceiveAndEmitOut : public QState
{
public:
    MessageReceiveAndEmitOut(UHV2Worker *parent, UHV2WorkerVarSet *VarSet, quint16 ReadTimeOutInMilisecond = 300);
    ~MessageReceiveAndEmitOut();
protected:
    void onEntry(QEvent *) override;
private:
    quint16 TimeOut4ReadInMilisecond = 0;
    QString * UniKey = Q_NULLPTR;
    UHV2Worker * parentPtr = Q_NULLPTR;
    UHV2WorkerVarSet * VarSetPtr = Q_NULLPTR;
};

#endif // MESSAGERECEIVEANDEMITOUT_H
