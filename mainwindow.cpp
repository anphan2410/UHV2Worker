#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    uhv2pump0(new BinaryProtocol(0))
{
    ui->setupUi(this);

    QThread *aNewThread = new QThread();
    UHV2Worker * anUHV2Worker = new UHV2Worker();
    anUHV2Worker->moveToThread(aNewThread);
    connect(aNewThread, &QThread::started, anUHV2Worker, &UHV2Worker::start);
    connect(this, &MainWindow::Out, anUHV2Worker, &UHV2Worker::In);
    connect(ui->pushButtonConnect, &QPushButton::clicked,
            this, [&](){
        anDebug("=> Button " + ui->pushButtonConnect->text() + " Clicked !");
        if (ui->pushButtonConnect->text() == "Connect")
        {
            emit Out(QVariant::fromValue(UHV2WorkerVarSet::ANewPortName), new QVariant(ui->comboBoxSerialPort->currentText()));
        }
        else if (ui->pushButtonConnect->text() == "Disconnect")
        {
            emit Out(QVariant::fromValue(UHV2WorkerVarSet::SerialPortDisconnect));
        }
        ui->pushButtonConnect->setText("Please Wait ...");
    });
    connect(ui->pushButtonHVonoff, &QPushButton::clicked,
            this, [&](){
        anDebug("=> Button " + ui->pushButtonHVonoff->text() + " Clicked !");
        if (ui->pushButtonHVonoff->text() != "")
        {
            UHV2WorkerVarSet::PrioritizedCommandMessage hvOnMsg;
            hvOnMsg.first = ui->spinBoxHVonoff->value();
            hvOnMsg.second = new UHV2WorkerVarSet::CommandMessage(new QByteArray(uhv2pump0->HVSwitch().On().Ch1().GenMsg()),
                                                                   new QString());
            emit Out(QVariant::fromValue(UHV2WorkerVarSet::AnUHV2PrioritizedCommandMessage), new QVariant(QVariant::fromValue(hvOnMsg)));
        }
        else if (ui->pushButtonHVonoff->text() == "HV OFF")
        {
            emit Out(QVariant::fromValue(UHV2WorkerVarSet::SerialPortDisconnect));
        }
        ui->pushButtonHVonoff->setText("WAIT");
    });
    connect(anUHV2Worker, &UHV2Worker::Out, this, &MainWindow::In);

    foreach (QSerialPortInfo currentScan, QSerialPortInfo::availablePorts())
    {
        ui->comboBoxSerialPort->addItem(currentScan.portName());
    }

    aNewThread->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::In(QVariant AMessageTopic, QVariant *AMessageContent)
{
    if ( QString(AMessageTopic.typeName()) == "UHV2WorkerVarSet::MessageTopic")
    {
        switch (AMessageTopic.toInt()) {
        case UHV2WorkerVarSet::SerialPortConnect:
        {
            ui->pushButtonConnect->setText("Disconnect");
            break;
        }
        case UHV2WorkerVarSet::SerialPortDisconnect:
        {
            ui->pushButtonConnect->setText("Connect");
            break;
        }
        case UHV2WorkerVarSet::AnUHV2PrioritizedCommandMessage:
        {
            anDebug("=> AnUHV2PrioritizedReplyMessage Received !");
            UHV2WorkerVarSet::PrioritizedCommandMessage * newRepMsg
                    = new UHV2WorkerVarSet::PrioritizedCommandMessage(AMessageContent->value<UHV2WorkerVarSet::PrioritizedCommandMessage>());
            ui->labelReadMsg->setText(newRepMsg->second->first->toHex());
            break;
        }
        case UHV2WorkerVarSet::MessageReadTimedOut:
        {
            ui->labelReadMsg->setStyleSheet("QLabel { background-color : gray; color : red; }");
            ui->labelReadMsg->clear();
            ui->labelReadMessage->setText("Timed Out To Read !");
            break;
        }
        case UHV2WorkerVarSet::MessageSendTimedOut:
        {
            ui->labelReadMsg->setStyleSheet("QLabel { background-color : gray; color : red; }");
            ui->labelSentMsg->clear();
            ui->labelSentMessage->setText("Timed Out To Send !");
            break;
        }
        default:
            break;
        }
    }
}
