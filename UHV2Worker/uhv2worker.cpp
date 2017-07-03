#include "uhv2worker.h"

UHV2Worker::UHV2Worker()
{
    anAck("Construct A New UHV2Worker !");
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
    state2->addTransition(WorkingVarSet->SerialPort, &QSerialPort::errorOccurred, state7);
    state2->addTransition(new UHV2WorkerDirectStateTransition(WorkingVarSet, state3));
    state2->addTransition(WorkingVarSet, &UHV2WorkerVarSet::PortNameChanged, state1);
    state3->addTransition(WorkingVarSet->SerialPort, &QSerialPort::errorOccurred, state7);
    state3->addTransition(new UHV2WorkerDirectStateTransition(WorkingVarSet, state4));
    state3->addTransition(WorkingVarSet, &UHV2WorkerVarSet::PortNameChanged, state1);
    state3->addTransition(WorkingVarSet, &UHV2WorkerVarSet::AFirstPrioritizedCommandMessageReceived, state3);
    state4->addTransition(WorkingVarSet->SerialPort, &QSerialPort::errorOccurred, state7);
    state4->addTransition(WorkingVarSet, &UHV2WorkerVarSet::PortNameChanged, state1);
    state4->addTransition(new UHV2WorkerDirectStateTransition(WorkingVarSet, state3));
    state7->addTransition(WorkingVarSet, &UHV2WorkerVarSet::PortNameChanged, state1);
    state7->addTransition(WorkingVarSet, &UHV2WorkerVarSet::RestartSerialPortConnection, state1);

    this->addState(state0);
    this->addState(state1);
    this->addState(state2);
    this->addState(state3);
    this->addState(state4);
    this->addState(state7);
    this->setInitialState(state0);
    this->setErrorState(state7);

    connect(WorkingVarSet->SerialPort, &QSerialPort::errorOccurred,
            this, [&](){ WorkingVarSet->ErrorStatus = UHV2WorkerVarSet::SerialPortError;});
    connect(WorkingVarSet, SIGNAL(Out(QVariant*,QVariant*)), this, SIGNAL(Out(QVariant*,QVariant*)));
    connect(state0, &QState::entered,
            this, [&](){ emit Out(new QVariant(QVariant::fromValue(UHV2WorkerVarSet::SerialPortDisconnect)));});
    connect(this, &QStateMachine::stopped,
            this, [&](){
        anAck("UHV2Worker Stopped !");
        WorkingVarSet->initialize();
    });
}

void UHV2Worker::In(QVariant *AnUHV2WorkerEnumValue, QVariant *rawData)
{
    anAck("An External Message Received !");
    if (QString(AnUHV2WorkerEnumValue->typeName()) == "UHV2WorkerVarSet::MessageTopic")
    {
        anAck("UHV2WorkerVarSet::MessageTopic Parsed !");
        switch (AnUHV2WorkerEnumValue->toInt()) {
        case UHV2WorkerVarSet::ANewPortName:
        {
            QString newPortName = rawData->toString();
            if (newPortName != "")
            {
                anAck("ANewPortName Received !");
                *(WorkingVarSet->PortName) = newPortName;
                anVar(*(WorkingVarSet->PortName));
                anInfo("Emit PortNameChanged() ...");
                emit WorkingVarSet->PortNameChanged();
            }
            break;
        }
        case UHV2WorkerVarSet::AnUHV2PrioritizedCommandMessage:
        {
            anAck("AnUHV2PrioritizedCommandMessage Received !");
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
//This is used for direct testing and revise
//            if (WorkingVallllllrSet->PendingMessageList->contains(0))
//                qDebug() << "   I : " << WorkingVarSet->PendingMessageList->value(0)->size()
//                         << " Priority 0";
//            if (WorkingVarSet->PendingMessageList->contains(1))
//                qDebug() << "   V : " << WorkingVarSet->PendingMessageList->value(1)->size()
//                         << " Priority 1";
//            if (WorkingVarSet->PendingMessageList->contains(5))
//                qDebug() << "   P : " << WorkingVarSet->PendingMessageList->value(5)->size()
//                         << " Priority 5";
            if (WorkingVarSet->PendingMessageList->size() == 1)
            {
                if (WorkingVarSet->PendingMessageList->first()->size() == 1)
                {
                    emit WorkingVarSet->AFirstPrioritizedCommandMessageReceived();
                }
            }
            break;
        }
        case UHV2WorkerVarSet::SerialPortRestart:
        {
            emit WorkingVarSet->RestartSerialPortConnection();
            break;
        }
        case UHV2WorkerVarSet::SerialPortDisconnect:
        {
            anAck("SerialPortDisconnect Received !");
            *(WorkingVarSet->PortName) = "";
            emit WorkingVarSet->PortNameChanged();
            break;
        }
        case UHV2WorkerVarSet::PendingMessageListClear:
        {
            anAck("PendingMessageListClear Received !");
            WorkingVarSet->PendingMessageList->clear();
            anAck("PendingMessageList Cleared !");
            emit Out(new QVariant(QVariant::fromValue(UHV2WorkerVarSet::PendingMessageListClear)));
            break;
        }
        default:
            break;
        }
    }
}
