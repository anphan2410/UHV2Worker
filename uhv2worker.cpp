#include "uhv2worker.h"

UHV2Worker::UHV2Worker(QObject *parent) : QObject(parent), UHV2SerialPort(new QSerialPort())
{
    anDebugWrap(UHV2WorkerDebug,anDebug("New UHV2Worker Object Created !"));
}

void UHV2Worker::NewConfigRequestUHV2SerialPort(const QString &NewPortName)
{
    anDebugWrap(UHV2WorkerDebug,
                anDebugWrap(PortName != NewPortName,
                anDebug("UHV2WorkerSerialPort Changed !");
                anqDebug(_VarView(PortName));
                ));
    PortName = NewPortName;
}

void UHV2Worker::Initialization()
{
    if (UHV2SerialPort->isOpen())
    {
        UHV2SerialPort->close();
    }
    anDebugWrap(UHV2WorkerDebug,
                anDebugWrap(PortName.isEmpty() || PortName.isNull(),
                anDebug("Wait for a nonempty PortName !");
                ));
    while (PortName.isEmpty() || PortName.isNull())
    {
        qApp->processEvents();
    }
    anDebugWrap(UHV2WorkerDebug,
                anDebug("Valid PortName !");
                anqDebug(_VarView(PortName));
                );
    UHV2SerialPort.setReadBufferSize(64);
    UHV2SerialPort.setDataBits(QSerialPort::Data8);
    UHV2SerialPort.setBaudRate(QSerialPort::Baud9600);
    UHV2SerialPort.setStopBits(QSerialPort::OneStop);
    UHV2SerialPort.setParity(QSerialPort::NoParity);
    UHV2SerialPort.setFlowControl(QSerialPort::NoFlowControl);
    UHV2SerialPort.setPortName(PortName);
    anDebugWrap(UHV2WorkerDebug,anDebug("UHV2SerialPort Configured !"));
    quint8 count0 = 0;
    while (!UHV2SerialPort->open(QIODevice::ReadWrite))
    {
        if (++count0>3)
        {
            emit UHV2WorkerStopped();
            stop();
            anDebugWrap(UHV2WorkerDebug,anDebug("ERROR CANNOT Connect UHV2SerialPort !"));
            return;
        }
        qApp->processEvents();
    }
    anDebugWrap(UHV2WorkerDebug,anDebug("UHV2SerialPort Is Connected !"));
    //currentState=...
}

void UHV2Worker::start()
{
    anDebugWrap(UHV2WorkerDebug,anDebug("Start Button Pressed !"));
    currentState = &Initialization;
    isContinuous = true;
    while (currentState != NULL)
    {
        qApp->processEvents();
        if (isContinuous)
        {
            anDebugWrap(UHV2WorkerDebug,anDebug("Check In The Work Loop !"));
            qApp->processEvents();
            currentState();
            if (!isContinuous)
            {
                anDebugWrap(UHV2WorkerDebug,anDebug("Pause Button Pressed !"));
            }
        }
    }
    anDebugWrap(UHV2WorkerDebug,anDebug("Stop Button Pressed !"));
}

void UHV2Worker::resume()
{
    isContinuous = true;
    anDebugWrap(UHV2WorkerDebug,anDebug("Resume Button Requested !"));
}

void UHV2Worker::pause()
{
    isContinuous = false;
    anDebugWrap(UHV2WorkerDebug,anDebug("Pause Button Requested !"));
}

void UHV2Worker::stop()
{
    isContinuous = false;
    currentState = NULL;
    anDebugWrap(UHV2WorkerDebug,anDebug("Stop Button Requested !"));
}
