#include "uhv2worker.h"

UHV2Worker::UHV2Worker()
{

}

void UHV2Worker::setPortName(const QString &NewPortName)
{
    PortName = new QString(NewPortName);
    emit PortNameChanged(*PortName);
}
