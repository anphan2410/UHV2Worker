#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSerialPort *test = new QSerialPort("COM1");
    QSerialPort *test2 = new QSerialPort("COM1");
    connect(test, &QSerialPort::errorOccurred, [=](QSerialPort::SerialPortError error){qDebug() << "test error " << error;});
    connect(test2, &QSerialPort::errorOccurred, [=](QSerialPort::SerialPortError error){qDebug() << "test2 error " << error;});
    qDebug() << "try : " << test->open(QIODevice::ReadWrite);
    qDebug() << test->isOpen();

    qDebug() << "try : " << test2->open(QIODevice::ReadWrite);
    qDebug() << test2->isOpen();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

}
