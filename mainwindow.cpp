#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPixmap"
#include "QScrollBar"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix("E:/Năm 3/Photo/Logo_BK.png");
    int w = ui -> label_pic -> width();
    int h = ui -> label_pic -> height();
    ui -> label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
    // Disable maximizing
    setFixedSize(width(), height());

    // Adding title for widget
    QMainWindow::setWindowTitle("Serial Port");

    // Ports
    QList<QSerialPortInfo> ports = info.availablePorts();
    QList<QString> stringPorts;
    for(int i = 0 ; i < ports.size() ; i++){
        stringPorts.append(ports.at(i).portName());
    }
    ui->comboBox->addItems(stringPorts);

    // Baud Rate Ratios
    QList<qint32> baudRates = info.standardBaudRates(); // What baudrates does my computer support ?
    QList<QString> stringBaudRates;
    for(int i = 0 ; i < baudRates.size() ; i++){
        stringBaudRates.append(QString::number(baudRates.at(i)));
    }
    ui->comboBox_2->addItems(stringBaudRates);

    // Data Bits
    ui->comboBox_3->addItem("5");
    ui->comboBox_3->addItem("6");
    ui->comboBox_3->addItem("7");
    ui->comboBox_3->addItem("8");

    // Stop Bits
    ui->comboBox_4->addItem("1 Bit");
    ui->comboBox_4->addItem("1,5 Bits");
    ui->comboBox_4->addItem("2 Bits");

    // Parities
    ui->comboBox_5->addItem("No Parity");
    ui->comboBox_5->addItem("Even Parity");
    ui->comboBox_5->addItem("Odd Parity");
    ui->comboBox_5->addItem("Mark Parity");
    ui->comboBox_5->addItem("Space Parity");

    //Flow Controls
    ui->comboBox_6->addItem("No Flow Control");
    ui->comboBox_6->addItem("Hardware Flow Control");
    ui->comboBox_6->addItem("Software Flow Control");

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_2_clicked()
{


    QString portName = ui->comboBox->currentText();
    serialPort.setPortName(portName);

    serialPort.open(QIODevice::ReadWrite);

    if(!serialPort.isOpen()){
        ui->textBrowser->setTextColor(Qt::red);
        ui->textBrowser->append("!!!! Something went Wrong !!!!");
    }
    else {

        QString stringbaudRate = ui->comboBox_2->currentText();
        int intbaudRate = stringbaudRate.toInt();
        serialPort.setBaudRate(intbaudRate);

        QString dataBits = ui->comboBox_3->currentText();
        if(dataBits == "5 Bits") {
            serialPort.setDataBits(QSerialPort::Data5);
        }
        else if((dataBits == "6 Bits")) {
            serialPort.setDataBits(QSerialPort::Data6);
        }
        else if(dataBits == "7 Bits") {
            serialPort.setDataBits(QSerialPort::Data7);
        }
        else if(dataBits == "8 Bits"){
            serialPort.setDataBits(QSerialPort::Data8);
        }

        QString stopBits = ui->comboBox_4->currentText();
        if(stopBits == "1 Bit") {
            serialPort.setStopBits(QSerialPort::OneStop);
        }
        else if(stopBits == "1,5 Bits") {
            serialPort.setStopBits(QSerialPort::OneAndHalfStop);
        }
        else if(stopBits == "2 Bits") {
            serialPort.setStopBits(QSerialPort::TwoStop);
        }

        QString parity = ui->comboBox_5->currentText();
        if(parity == "No Parity"){
            serialPort.setParity(QSerialPort::NoParity);
        }
        else if(parity == "Even Parity"){
            serialPort.setParity(QSerialPort::EvenParity);
        }
        else if(parity == "Odd Parity"){
            serialPort.setParity(QSerialPort::OddParity);
        }
        else if(parity == "Mark Parity"){
            serialPort.setParity(QSerialPort::MarkParity);
        }
        else if(parity == "Space Parity") {
            serialPort.setParity(QSerialPort::SpaceParity);
        }


        QString flowControl = ui->comboBox_6->currentText();
        if(flowControl == "No Flow Control") {
            serialPort.setFlowControl(QSerialPort::NoFlowControl);
        }
        else if(flowControl == "Hardware Flow Control") {
            serialPort.setFlowControl(QSerialPort::HardwareControl);
        }
        else if(flowControl == "Software Flow Control") {
            serialPort.setFlowControl(QSerialPort::SoftwareControl);
        }
       connect(&serialPort,SIGNAL(readyRead()),this,SLOT(receiveMessage()));
    }
}

void MainWindow::receiveMessage()
{
    QByteArray dataBA = serialPort.readAll();
    QString data(dataBA);
    ui->textBrowser->setTextColor(Qt::blue); // Receieved message's color is blue.
    ui->textBrowser->insertPlainText(data);
    QScrollBar *sb = ui->textBrowser->verticalScrollBar();
    sb->setValue(sb->maximum());

}


void MainWindow::on_pushButton_clicked()
{
    QString message = ui->lineEdit_2->text();
    ui->textBrowser->setTextColor(Qt::darkGreen); // Color of message to send is green.
    ui->textBrowser->append(message);
    serialPort.write(message.toUtf8());
}

// Button of Disconnect

void MainWindow::on_pushButton_3_clicked()
{
    serialPort.close();
}
// Button of Refresh Ports


void MainWindow::on_pushButton_4_clicked()
{
    ui->comboBox->clear();
    QList<QSerialPortInfo> ports = info.availablePorts();
    QList<QString> stringPorts;
    for(int i = 0 ; i < ports.size() ; i++){
        stringPorts.append(ports.at(i).portName());
    }
    ui->comboBox->addItems(stringPorts);
}

// Button of Clear

void MainWindow::on_pushButton_5_clicked()
{
    ui->textBrowser->clear();
}

