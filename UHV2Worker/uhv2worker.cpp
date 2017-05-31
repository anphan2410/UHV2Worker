#include "uhv2worker.h"

UHV2Worker::UHV2Worker()
{

}

void UHV2Worker::In(QVariant AnUHV2EnumValue, QVariant *rawData)
{
    switch (AnUHV2EnumValue.toInt()) {
    case UHV2WorkerVarSet::PortNameReply:
        if (rawData->toString() != "")
        {
            *(WorkingVarSet->PortName) = rawData->toString();
            emit WorkingVarSet->PortNameChanged();
        }
        break;
    default:
        break;
    }
}
