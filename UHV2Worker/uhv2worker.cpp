#include "uhv2worker.h"

UHV2Worker::UHV2Worker()
{
    anDebug("=> Construct A New UHV2Worker !");
    WorkingVarSet = new UHV2WorkerVarSet(this);
    SerialPortInfoRequest * state0 = new SerialPortInfoRequest(WorkingVarSet);
    state0->setObjectName("SerialPortInfoRequest");
    SerialPortInfoValidation * state1 = new SerialPortInfoValidation(WorkingVarSet);
    state1->setObjectName("SerialPortInfoValidation");
    SerialPortConnectionEstablishment * state2 = new SerialPortConnectionEstablishment(WorkingVarSet);
    state2->setObjectName("SerialPortConnectionEstablishment");
    SolitaryMessageTransmission * state3 = new SolitaryMessageTransmission(WorkingVarSet);
    state3->setObjectName("SolitaryMessageTransmission");
    MessageReceiveAndEmitOut * state4 = new MessageReceiveAndEmitOut(WorkingVarSet);
    state4->setObjectName("MessageReceiveAndEmitOut");
    ErrorAnnouncement * state7 = new ErrorAnnouncement(WorkingVarSet);
    state7->setObjectName("ErrorAnnouncement");

    state0->addTransition(WorkingVarSet, &UHV2WorkerVarSet::PortNameChanged, state1);
    state1->addTransition(WorkingVarSet, &UHV2WorkerVarSet::PortNameChanged, state1);
    state1->addTransition(new UHV2WorkerDirectStateTransition(WorkingVarSet, state0));
    state1->addTransition(new UHV2WorkerDirectStateTransition(WorkingVarSet, state2));
    state2->addTransition(new QSignalTransition(WorkingVarSet->SerialPort, &QSerialPort::errorOccurred, state7));
    state2->addTransition(new UHV2WorkerDirectStateTransition(WorkingVarSet, state3));
    state2->addTransition(WorkingVarSet, &UHV2WorkerVarSet::PortNameChanged, state1);
    state3->addTransition(new QSignalTransition(WorkingVarSet->SerialPort, &QSerialPort::errorOccurred, state7));
    state3->addTransition(new QSignalTransition(WorkingVarSet->SerialPort, &QSerialPort::readyRead, state4));
    state3->addTransition(WorkingVarSet, &UHV2WorkerVarSet::PortNameChanged, state1);
    state4->addTransition(new QSignalTransition(WorkingVarSet->SerialPort, &QSerialPort::errorOccurred, state7));
    state4->addTransition(WorkingVarSet, &UHV2WorkerVarSet::PortNameChanged, state1);
    state7->addTransition(WorkingVarSet, &UHV2WorkerVarSet::PortNameChanged, state1);
    state7->addTransition(WorkingVarSet, &UHV2WorkerVarSet::RestartSerialPortConnection, state2);

    this->addState(state0);
    this->addState(state1);
    this->addState(state2);
    this->addState(state3);
    this->addState(state4);
    this->addState(state7);

    connect(WorkingVarSet, SIGNAL(Out(QVariant,QVariant*)), this, SIGNAL(Out(QVariant,QVariant*));
}

void UHV2Worker::In(QVariant AnUHV2WorkerEnumValue, QVariant *rawData)
{
    switch (AnUHV2WorkerEnumValue.toInt()) {
    case UHV2WorkerVarSet::PortNameReply:
        if (rawData->toString() != "")
        {
            *(WorkingVarSet->PortName) = rawData->toString();
            emit WorkingVarSet->PortNameChanged();
        }
        break;
    case UHV2WorkerVarSet::UHV2PrioritizedCommandMessage:
        UHV2WorkerVarSet::PrioritizedCommandMessage * newCmdMsg
                = new UHV2WorkerVarSet::PrioritizedCommandMessage(rawData->value<UHV2WorkerVarSet::PrioritizedCommandMessage>());
        if (WorkingVarSet->PendingMessageList->contains(newCmdMsg->first))
        {
            WorkingVarSet->PendingMessageList->value(newCmdMsg->first)->append(newCmdMsg->second);
        }
        else
        {
            WorkingVarSet->PendingMessageList->insert(newCmdMsg->first, new QList<UHV2WorkerVarSet::CommandMessage*>({newCmdMsg->second}));
        }
        break;
    case UHV2WorkerVarSet::RestartSerialPort:
        emit WorkingVarSet->RestartSerialPortConnection();
        break;
    default:
        break;
    }
}
