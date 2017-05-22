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

    typedef void (*vovaFnctr)();

    static constexpr const quint8 WriteTimeOut = 100;
    static constexpr const quint16 ReadTimeOut = 300;

    vovaFnctr currentState;
    bool isContinuous = false;

    QString PortName = "";
    QMap<quint8,QList<UHV2WorkerCommandMessage*>*> CommandList;
    QSerialPort *UHV2SerialPort;

    void Initialization();
    void SendAndRead();
public:

    typedef struct
    {
        quint8 Priority = 0;
        QByteArray * Message;
        QString * UniqueKey;
    } UHV2WorkerCommandMessage;

    explicit UHV2Worker(QObject *parent = 0);
signals:
    void UHV2WorkerStopped();
public slots:    
    void NewConfigRequestUHV2SerialPort(const QString &NewPortName);
    void start();
    void resume();
    void pause();
    void stop();
};

#endif // UHV2WORKER_H
