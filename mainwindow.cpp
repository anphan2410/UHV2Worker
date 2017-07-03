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
        anAck("Button " + ui->pushButtonConnect->text() + " Clicked !");
        if (ui->pushButtonConnect->text() == "Connect")
        {
            emit Out(new QVariant(QVariant::fromValue(UHV2WorkerVarSet::ANewPortName)),
                     new QVariant(ui->comboBoxSerialPort->currentText()));
        }
        else if (ui->pushButtonConnect->text() == "Disconnect")
        {
            emit Out(new QVariant(QVariant::fromValue(UHV2WorkerVarSet::SerialPortDisconnect)));
        }
        ui->pushButtonConnect->setText("Please Wait ...");
    });
    connect(ui->pushButtonHVonoff, &QPushButton::clicked,
            this, [&](){
        anAck("Button " + ui->pushButtonHVonoff->text() + " Clicked !");
        if (ui->pushButtonHVonoff->text() == "HV ON")
        {
            UHV2WorkerVarSet::PrioritizedCommandMessage hvOnMsg;
            hvOnMsg.first = ui->spinBoxHVonoff->value();
            hvOnMsg.second = new UHV2WorkerVarSet::CommandMessage(new QByteArray(uhv2pump0->HVSwitch().On().Ch1().GenMsg()),
                                                                   new QString());
            for (quint8 index=0; index<=ui->spinBoxHVonoff_2->value(); ++index)
            {
                emit Out(new QVariant(QVariant::fromValue(UHV2WorkerVarSet::AnUHV2PrioritizedCommandMessage)),
                         new QVariant(QVariant::fromValue(hvOnMsg)));
            }
        }
        else if (ui->pushButtonHVonoff->text() == "HV OFF")
        {
            UHV2WorkerVarSet::PrioritizedCommandMessage hvOffMsg;
            hvOffMsg.first = ui->spinBoxHVonoff->value();
            hvOffMsg.second = new UHV2WorkerVarSet::CommandMessage(new QByteArray(uhv2pump0->HVSwitch().Off().Ch1().GenMsg()),
                                                                   new QString());
            for (quint8 index=0; index<=ui->spinBoxHVonoff_2->value(); ++index)
            {
                emit Out(new QVariant(QVariant::fromValue(UHV2WorkerVarSet::AnUHV2PrioritizedCommandMessage)),
                         new QVariant(QVariant::fromValue(hvOffMsg)));
            }
        }
        ui->pushButtonHVonoff->setText("WAIT");
    });

    connect(ui->pushButtonReadI, &QPushButton::clicked,
            this, [&](){
        UHV2WorkerVarSet::PrioritizedCommandMessage readIstatusMsg;
        readIstatusMsg.first = ui->spinBoxReadI->value();
        readIstatusMsg.second = new UHV2WorkerVarSet::CommandMessage(new QByteArray(uhv2pump0->ReadI().Ch1().GenMsg()),
                                                                     new QString());
        for (quint8 index=0; index<=ui->spinBoxReadI_2->value(); ++index)
        {
            emit Out(new QVariant(QVariant::fromValue(UHV2WorkerVarSet::AnUHV2PrioritizedCommandMessage)),
                     new QVariant(QVariant::fromValue(readIstatusMsg)));
        }
    });

    connect(ui->pushButtonReadV, &QPushButton::clicked,
            this, [&](){
        UHV2WorkerVarSet::PrioritizedCommandMessage ReadVstatusMsg;
        ReadVstatusMsg.first = ui->spinBoxReadV->value();
        ReadVstatusMsg.second = new UHV2WorkerVarSet::CommandMessage(new QByteArray(uhv2pump0->ReadV().Ch1().GenMsg()),
                                                                     new QString());
        for (quint8 index=0; index<=ui->spinBoxReadV_2->value(); ++index)
        {
            emit Out(new QVariant(QVariant::fromValue(UHV2WorkerVarSet::AnUHV2PrioritizedCommandMessage)),
                     new QVariant(QVariant::fromValue(ReadVstatusMsg)));
        }
    });

    connect(ui->pushButtonReadP, &QPushButton::clicked,
            this, [&](){
        UHV2WorkerVarSet::PrioritizedCommandMessage ReadPstatusMsg;
        ReadPstatusMsg.first = ui->spinBoxReadP->value();
        ReadPstatusMsg.second = new UHV2WorkerVarSet::CommandMessage(new QByteArray(uhv2pump0->ReadP().Ch1().GenMsg()),
                                                                     new QString());
        for (quint8 index=0; index<=ui->spinBoxReadP_2->value(); ++index)
        {
            emit Out(new QVariant(QVariant::fromValue(UHV2WorkerVarSet::AnUHV2PrioritizedCommandMessage)),
                     new QVariant(QVariant::fromValue(ReadPstatusMsg)));
        }
    });

    connect(anUHV2Worker, &UHV2Worker::Out, this, &MainWindow::In);

    connect(ui->pushButtonClearBuffer, &QPushButton::clicked,
            this, [&](){
        emit Out(new QVariant(QVariant::fromValue(UHV2WorkerVarSet::PendingMessageListClear)));
    });
    connect(ui->pushButton, &QPushButton::clicked, ui->pushButtonReadI, &QPushButton::click);
    connect(ui->pushButton, &QPushButton::clicked, ui->pushButtonReadV, &QPushButton::click);
    connect(ui->pushButton, &QPushButton::clicked, ui->pushButtonReadP, &QPushButton::click);

    foreach (QSerialPortInfo currentScan, QSerialPortInfo::availablePorts())
    {
        ui->comboBoxSerialPort->addItem(currentScan.portName());
    }

    aNewThread->start();
}

MainWindow::~MainWindow()
{
    qApp->processEvents();
    delete ui;
}

void MainWindow::In(QVariant *AMessageTopic, QVariant *AMessageContent)
{
    anAck("An External Message Received !");
    if ( QString(AMessageTopic->typeName()) == "UHV2WorkerVarSet::MessageTopic")
    {
        anAck("UHV2WorkerVarSet::MessageTopic Parsed !");
        switch (AMessageTopic->toInt()) {
        case UHV2WorkerVarSet::SerialPortConnect:
        {
            anInfo("SerialPortConnect Received !");
            ui->pushButtonConnect->setText("Disconnect");
            break;
        }
        case UHV2WorkerVarSet::SerialPortDisconnect:
        {
            anInfo("SerialPortDisconnect Received !");
            ui->pushButtonConnect->setText("Connect");
            break;
        }
        case UHV2WorkerVarSet::AnUHV2PrioritizedCommandMessage:
        {
            anInfo("AnUHV2PrioritizedReplyMessage Received !");
            UHV2WorkerVarSet::PrioritizedCommandMessage * newRepMsg
                    = new UHV2WorkerVarSet::PrioritizedCommandMessage(AMessageContent->value<UHV2WorkerVarSet::PrioritizedCommandMessage>());
            QByteArray * coreRepMsg = newRepMsg->second->first;
            if (coreRepMsg->size() > 7)
            {
                BinaryProtocol & tmpUHV2 = BinaryProtocol::BP(*(coreRepMsg));
                if (tmpUHV2.GetMessageDirection() == "From")
                {
                    anInfo("Read: " << tmpUHV2.GetMessageTranslation());
                    updateSENDlabel("",ui->labelSentMsg->text(),ui->labelSentMessage->text());
                    updateREADlabel("QLabel { background-color : green; color : yellow; }",tmpUHV2.GetMsg().toHex(),tmpUHV2.GetMessageTranslation());
                    if (ui->labelSentMessage->text().contains("Off", Qt::CaseInsensitive)
                            && ui->labelSentMessage->text().contains("HVSwitch", Qt::CaseInsensitive))
                        ui->pushButtonHVonoff->setText("HV ON");
                }
                else if (tmpUHV2.GetMessageDirection() == "To")
                {
                    anInfo("Sent: " << tmpUHV2.GetMessageTranslation());
                    updateREADlabel("",ui->labelReadMsg->text(),ui->labelReadMessage->text());
                    updateSENDlabel("QLabel { background-color : green; color : yellow; }",tmpUHV2.GetMsg().toHex(),tmpUHV2.GetMessageTranslation());
                }
            }
            else
            {
                anInfo("Read: " << coreRepMsg->toHex());
                updateSENDlabel("",ui->labelSentMsg->text(),ui->labelSentMessage->text());
                updateREADlabel("QLabel { background-color : green; color : yellow; }",coreRepMsg->toHex(),"");
                if ((QString(coreRepMsg->toHex()) == "06") && ui->labelSentMessage->text().contains("HVSwitch", Qt::CaseInsensitive))
                {
                    if (ui->labelSentMessage->text().contains("On", Qt::CaseInsensitive))
                    {
                        ui->pushButtonHVonoff->setText("HV OFF");
                    }
                    else if (ui->labelSentMessage->text().contains("Off", Qt::CaseInsensitive))
                    {
                        ui->pushButtonHVonoff->setText("HV ON");
                    }
                    ui->labelReadMessage->setText("Acknowledged");
                }
            }
            break;
        }
        case UHV2WorkerVarSet::MessageReadTimedOut:
        {
            anInfo("MessageReadTimedOut Received !");
            updateSENDlabel("",ui->labelSentMsg->text(),ui->labelSentMessage->text());
            updateREADlabel("QLabel { background-color : gray; color : red; }","","Timed Out To Read !");
            break;
        }
        case UHV2WorkerVarSet::MessageSendTimedOut:
        {
            anInfo("MessageSendTimedOut Received !");
            updateSENDlabel("QLabel { background-color : gray; color : red; }","","Timed Out To Send !");
            updateREADlabel("",ui->labelReadMsg->text(),ui->labelReadMessage->text());
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
