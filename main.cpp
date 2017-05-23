#include "mainwindow.h"
#include <QApplication>
#include <QHash>
#include <QDebug>
#include "uhv2worker.h"

int main(int argc, char *argv[])
{

    QMap<quint8,QList<UHV2Worker::CommandMessage*>*> CommandList;

    UHV2Worker::CommandMessage uwcm1;
    uwcm1.Message=new QByteArray("message1");
    uwcm1.Priority=3;
    uwcm1.UniqueKey=new QString("sdgasdfgdf");

    UHV2Worker::CommandMessage uwcm2;
    uwcm2.Message=new QByteArray("message2");
    uwcm2.Priority=5;
    uwcm2.UniqueKey=new QString("45ay54m8aertv");

    UHV2Worker::CommandMessage uwcm6;
    uwcm6.Message=new QByteArray("message6");
    uwcm6.Priority=1;
    uwcm6.UniqueKey=new QString("2334c2x342c2");

    CommandList.insert(uwcm1.Priority, new QList<UHV2Worker::CommandMessage*>({&uwcm1}));

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
