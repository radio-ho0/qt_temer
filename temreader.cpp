#include "temreader.h"
#include "ui_temreader.h"
#include "qextserialenumerator.h"
#include "parsetempr.h"
#include <QDebug>

TemReader::TemReader(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TemReader)
{
    ui->setupUi(this);

    foreach(QextPortInfo info, QextSerialEnumerator::getPorts()){
        ui->comPort->addItem(info.portName);
    }
    ui->comPort->setEditable(true);

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
    ui->comQueryMode->setCurrentIndex(1);
    ui->spinTimeout->setValue(200);

    isRunning = 0;
    allConnect();



    m_portSettings.BaudRate = (BaudRateType)ui->comBaudRate->itemData( ui->comBaudRate->currentIndex() ).toInt();
    m_portSettings.DataBits = (DataBitsType)ui->comDataBits->itemData( ui->comDataBits->currentIndex() ).toInt();
    m_portSettings.Parity = (ParityType)ui->comParify->itemData( ui->comParify->currentIndex() ).toInt();
    m_portSettings.StopBits = (StopBitsType)ui->comStopBits->itemData( ui->comStopBits->currentIndex()).toInt();
    m_portSettings.FlowControl = FLOW_OFF;
    m_portSettings.Timeout_Millisec = ui->spinTimeout->value();
    m_parseTempr = new parseTempr(this);
    connect(m_parseTempr, SIGNAL(sendData(QByteArray)), SLOT(slGetData(QByteArray)));

}

TemReader::~TemReader()
{
    delete ui;
}

void TemReader::allConnect()
{
    connect(ui->btOpenStop, SIGNAL(clicked()), SLOT(slStartStop()));
    connect(ui->spinTimeout, SIGNAL(valueChanged(int)), SLOT(slChangeTimeout()));
    connect(ui->btExit, SIGNAL(clicked()), SLOT(slExit()));
}

void TemReader::slStartStop()
{
    isRunning = !isRunning;
    if(isRunning){
        ui->lbStatus->setText(tr("For the tribe!"));
        QString name = ui->comPort->currentText();
        QextSerialPort::QueryMode m_queryMode = (QextSerialPort::QueryMode)ui->comQueryMode->currentIndex();
        //m_parseTempr->start(name, m_portSettings, QextSerialPort::Polling);
        m_parseTempr->start(name, m_portSettings, m_queryMode);
        qDebug() << "port name:: " <<  name << endl;
    }else{

        ui->lbStatus->setText(tr("I am stand ready!"));
        m_parseTempr->stopSerial();
    }


}

void TemReader::slGetData(QByteArray data)
{
    ui->plainData->moveCursor(QTextCursor::End);
    ui->plainData->insertPlainText(QString::fromLatin1( data ));

}

void TemReader::slChangeTimeout()
{
        m_portSettings.Timeout_Millisec = ui->spinTimeout->value();

}

void TemReader::slExit()
{
    m_parseTempr->stopSerial();
    this->deleteLater();

}

void TemReader::slPortChange()
{

}
