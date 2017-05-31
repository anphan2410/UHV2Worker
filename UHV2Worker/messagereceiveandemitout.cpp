#include "messagereceiveandemitout.h"

MessageReceiveAndEmitOut::MessageReceiveAndEmitOut(UHV2Worker *parent, UHV2WorkerVarSet *VarSet, quint16 ReadTimeOutInMilisecond)
    : QState(parent), parentPtr(parent), VarSetPtr(VarSet), TimeOut4ReadInMilisecond(ReadTimeOutInMilisecond)
{

}

MessageReceiveAndEmitOut::~MessageReceiveAndEmitOut()
{
    UniKey = Q_NULLPTR;
    parentPtr = Q_NULLPTR;
    VarSetPtr = Q_NULLPTR;
    delete UniKey;
    delete parentPtr;
    delete VarSetPtr;
}

void MessageReceiveAndEmitOut::onEntry(QEvent *)
{
    if (VarSetPtr->SerialPort->waitForReadyRead(TimeOut4ReadInMilisecond*10))
    {
        QByteArray tmpRead(VarSetPtr->SerialPort->readAll());
        while (VarSetPtr->SerialPort->waitForReadyRead(TimeOut4ReadInMilisecond))
        {
            tmpRead+=VarSetPtr->SerialPort->readAll();
        }
        VarSetPtr->lastReceivedMessage->first = Q_NULLPTR;
        VarSetPtr->lastReceivedMessage->second = Q_NULLPTR;
        VarSetPtr->lastReceivedMessage = new UHV2WorkerVarSet::CommandMessage();
        VarSetPtr->lastReceivedMessage->first = new QByteArray(tmpRead);
        VarSetPtr->lastReceivedMessage->second = VarSetPtr->lastTransmittedMessage->second;

        emit parentPtr->Out();
    }
}
