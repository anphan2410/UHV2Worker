#ifndef UHV2WORKER_H
#define UHV2WORKER_H
#define UHV2WorkerDebug 1

#include <QObject>
#include <QMap>
#include <QList>
#include <QtSerialPort>
#include "anqtdebug.h"

class UHV2Worker : public QObject
{
    Q_OBJECT
public:
    typedef struct
    {
        quint8 Priority = 0;
        QByteArray * Message;
        QString * UniqueKey;
    } CommandMessage;
    explicit UHV2Worker(QObject *parent = 0);
signals:
    void UHV2WorkerStopped();
public slots:
    void NewConfigRequestUHV2SerialPort(const QString &NewPortName);
    void start();
    void resume();
    void pause();
    void stop();

private:

    typedef void (UHV2Worker::*vovaFnctr)();

    static constexpr const quint8 WriteTimeOut = 100;
    static constexpr const quint16 ReadTimeOut = 300;

    vovaFnctr currentState;
    bool isContinuous = false;

    QString PortName = "";
    QMap<quint8,QList<CommandMessage*>*> CommandList;
    QSerialPort *UHV2SerialPort;

    void Initialization();
    void SendAndRead();
    void PauseAndResume();
};

#endif // UHV2WORKER_H
