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
        if (ui->pushButtonHVonoff->text() != "HV ON")
        {
            UHV2WorkerVarSet::PrioritizedCommandMessage hvOnMsg;
            hvOnMsg.first = ui->spinBoxHVonoff->value();
            hvOnMsg.second = new UHV2WorkerVarSet::CommandMessage(new QByteArray(uhv2pump0->HVSwitch().On().Ch1().GenMsg()),
                                                                   new QString());
            for (quint8 index=1; index<=ui->spinBoxHVonoff_2->value(); ++index)
            {
                emit Out(QVariant::fromValue(UHV2WorkerVarSet::AnUHV2PrioritizedCommandMessage), new QVariant(QVariant::fromValue(hvOnMsg)));
            }
        }
        else if (ui->pushButtonHVonoff->text() == "HV OFF")
        {
            UHV2WorkerVarSet::PrioritizedCommandMessage hvOffMsg;
            hvOffMsg.first = ui->spinBoxHVonoff->value();
            hvOffMsg.second = new UHV2WorkerVarSet::CommandMessage(new QByteArray(uhv2pump0->HVSwitch().Off().Ch1().GenMsg()),
                                                                   new QString());
            for (quint8 index=1; index<=ui->spinBoxHVonoff_2->value(); ++index)
            {
                emit Out(QVariant::fromValue(UHV2WorkerVarSet::AnUHV2PrioritizedCommandMessage), new QVariant(QVariant::fromValue(hvOffMsg)));
            }
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
    anDebug("=> An External Message Received !");
    if ( QString(AMessageTopic.typeName()) == "UHV2WorkerVarSet::MessageTopic")
    {
        anDebug("=> UHV2WorkerVarSet::MessageTopic Parsed !");
        switch (AMessageTopic.toInt()) {
        case UHV2WorkerVarSet::SerialPortConnect:
        {
            anqDebug("=> SerialPortConnect Received !");
            ui->pushButtonConnect->setText("Disconnect");
            break;
        }
        case UHV2WorkerVarSet::SerialPortDisconnect:
        {
            anqDebug("=> SerialPortDisconnect Received !");
            ui->pushButtonConnect->setText("Connect");
            break;
        }
        case UHV2WorkerVarSet::AnUHV2PrioritizedCommandMessage:
        {
            anqDebug("=> AnUHV2PrioritizedReplyMessage Received !");
            UHV2WorkerVarSet::PrioritizedCommandMessage * newRepMsg
                    = new UHV2WorkerVarSet::PrioritizedCommandMessage(AMessageContent->value<UHV2WorkerVarSet::PrioritizedCommandMessage>());
            BinaryProtocol tmpUHV2 = BinaryProtocol::BP(*(newRepMsg->second->first));
            ui->labelSEND->setStyleSheet("");
            ui->labelSentMsg->setStyleSheet("");
            ui->labelSentMessage->setStyleSheet("");
            ui->labelREAD->setStyleSheet("QLabel { background-color : green; color : purple; }");
            ui->labelReadMsg->setStyleSheet("QLabel { background-color : green; color : purple; }");
            ui->labelReadMsg->setText(tmpUHV2.GetMsg().toHex());
            ui->labelReadMessage->setStyleSheet("QLabel { background-color : green; color : purple; }");
            ui->labelReadMessage->setText(tmpUHV2.GetMessageTranslation());
            break;
        }
        case UHV2WorkerVarSet::MessageReadTimedOut:
        {
            anqDebug("=> MessageReadTimedOut Received !");
            ui->labelREAD->setStyleSheet("QLabel { background-color : gray; color : red; }");
            ui->labelReadMsg->setStyleSheet("QLabel { background-color : gray; color : red; }");
            ui->labelReadMsg->clear();
            ui->labelReadMessage->setStyleSheet("QLabel { background-color : gray; color : red; }");
            ui->labelReadMessage->setText("Timed Out To Read !");
            break;
        }
        case UHV2WorkerVarSet::MessageSendTimedOut:
        {
            anqDebug("=> MessageSendTimedOut Received !");
            ui->labelSEND->setStyleSheet("QLabel { background-color : gray; color : red; }");
            ui->labelSentMsg->setStyleSheet("QLabel { background-color : gray; color : red; }");
            ui->labelSentMsg->clear();
            ui->labelSentMessage->setStyleSheet("QLabel { background-color : gray; color : red; }");
            ui->labelSentMessage->setText("Timed Out To Send !");
            break;
        }
        default:
            break;
        }
    }
}

void MainWindow::updateSENDlabel(const QString &SENDstyleSheet, const QString &SentMsgStr, const QString &SentMessageStr)
{
    ui->labelSEND->setStyleSheet(SENDstyleSheet);
    ui->labelSentMsg->setStyleSheet(SENDstyleSheet);
    ui->labelSentMsg->setText(SentMsgStr);
    ui->labelSentMessage->setStyleSheet(SENDstyleSheet);
    ui->labelSentMessage->setText(SentMessageStr);
    ui->labelSEND->update();
    ui->labelSentMsg->update();
    ui->labelSentMessage->update();
}

void MainWindow::updateREADlabel(const QString &READstyleSheet, const QString &ReadMsgStr, const QString &ReadMessageStr)
{
    ui->labelREAD->setStyleSheet(READstyleSheet);
    ui->labelReadMsg->setStyleSheet(READstyleSheet);
    ui->labelReadMsg->setText(ReadMsgStr);
    ui->labelReadMessage->setStyleSheet(READstyleSheet);
    ui->labelReadMessage->setText(ReadMessageStr);
    ui->labelREAD->update();
    ui->labelReadMsg->update();
    ui->labelReadMessage->update();
}
