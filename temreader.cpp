#include "temreader.h"
#include "ui_temreader.h"
#include "qextserialport.h"

TemReader::TemReader(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TemReader)
{
    ui->setupUi(this);
    ui-> comBaudRate->addItem("1200", BAUD1200);
    ui-> comBaudRate->addItem("2400", BAUD2400);
    ui-> comBaudRate->addItem("4800", BAUD4800);
    ui-> comBaudRate->addItem("9600", BAUD9600);
    ui-> comBaudRate->addItem("19200", BAUD19200);
    ui-> comBaudRate->addItem("115200", BAUD115200);
    ui-> comBaudRate->setCurrentIndex(3);

    ui->comParify->addItem("NONE", PAR_NONE);
    ui->comParify->addItem("ODD", PAR_ODD);
    ui->comParify->addItem("EVEN", PAR_EVEN);

    ui->comDataBits->addItem("5", DATA_5);
    ui->comDataBits->addItem("6", DATA_6);
    ui->comDataBits->addItem("7", DATA_7);
    ui->comDataBits->addItem("8", DATA_8);
    ui->comDataBits->setCurrentIndex(3);

    ui->comStopBits->addItem("1", STOP_1);
    ui->comStopBits->addItem("2", STOP_2);

    ui->comQueryMode->addItem("Polling", QextSerialPort::Polling);
    ui->comQueryMode->addItem("EventDriven", QextSerialPort::EventDriven);

}

TemReader::~TemReader()
{
    delete ui;
}
