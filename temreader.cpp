#include "temreader.h"
#include "ui_temreader.h"
#include "qextserialenumerator.h"
#include "parsetempr.h"
#include <qwt_dial_needle.h>
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
    //m_parseTempr = new parseTempr(this);
    m_parseTempr = new parseTempr();
    connect(m_parseTempr, SIGNAL(sendData(QByteArray)), SLOT(slGetData(QByteArray)));
    connect(m_parseTempr, SIGNAL(sendTargetStr(QByteArray)), SLOT(slGetTargetString(QByteArray)));

    threadTemp = new QThread(this);
    m_parseTempr->moveToThread(threadTemp);
    connect(threadTemp, SIGNAL(finished()), threadTemp, SLOT(deleteLater()));
    threadTemp->start();

    ui->diaHiTemp->setValue(0.0);
    ui->diaTemp->setValue(0.0);
    ui->thermoHumi->setValue(0.0);

    ui->diaHiTemp->setNeedle( new QwtDialSimpleNeedle( QwtDialSimpleNeedle::Ray,
                                                       true, Qt::black )   );
    ui->diaTemp->setNeedle( new QwtDialSimpleNeedle( QwtDialSimpleNeedle::Ray,
                                                     true, Qt::green )   );

}

TemReader::~TemReader()
{
    delete ui;
    threadTemp->quit();
    threadTemp->wait();
}

void TemReader::allConnect()
{
    connect(ui->btOpenStop, SIGNAL(clicked()), SLOT(slStartStop()));
    connect(ui->spinTimeout, SIGNAL(valueChanged(int)), SLOT(slChangeTimeout()));
    connect(ui->btExit, SIGNAL(clicked()), SLOT(slExit()));
    connect(ui->comBaudRate, SIGNAL(currentIndexChanged(int)), SLOT(slBaudRateChange(int)));
    connect(ui->comDataBits, SIGNAL(currentIndexChanged(int)), SLOT(slDataBitsChange(int)));
    connect(ui->comParify, SIGNAL(currentIndexChanged(int)), SLOT(slParifyChange(int)));
    connect(ui->comQueryMode, SIGNAL(currentIndexChanged(int)),
            SLOT(slQueryModeChange(int)));
    connect(ui->comStopBits, SIGNAL(currentIndexChanged(int)),SLOT(slStopBitsChange(int)));

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
        ui->tabWidget->setCurrentWidget(ui->tab_2);
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

void TemReader::slGetTargetString(QByteArray data)
{

    QStringList list = QString::fromUtf8(data).split(',');
    double hiTemp = list.at( parseTempr::HI_TEMP_OFFSET ).toDouble();
    double humidity = list.at( parseTempr::HUMIDITY_OFFSET ).toDouble();
    double temp = list.at( parseTempr::TEMP_OFFSET ).toDouble();
    double tempf = list.at( parseTempr::TEMPF_OFFSET ).toDouble();

    ui->spinHiTemp->setValue(hiTemp);
    ui->spinHumi->setValue(humidity);
    ui->spinTemp->setValue(temp);
    ui->spinTempf->setValue(tempf);

    ui->diaHiTemp->setValue(hiTemp);
    ui->diaTemp->setValue(temp);
    ui->thermoHumi->setValue(humidity);


}

void TemReader::slBaudRateChange(int idx)
{
    m_portSettings.BaudRate = (BaudRateType)ui->comBaudRate->itemData( idx ).toInt();

}

void TemReader::slParifyChange(int idx)
{
    m_portSettings.Parity = (ParityType)ui->comParify->itemData( idx ).toInt();
}

void TemReader::slDataBitsChange(int idx)
{
    m_portSettings.DataBits = (DataBitsType)ui->comDataBits->itemData( idx ).toInt();
}

void TemReader::slStopBitsChange(int idx)
{
    m_portSettings.StopBits = (StopBitsType)ui->comStopBits->itemData( idx ).toInt();
}

void TemReader::slQueryModeChange(int idx)
{
    Q_UNUSED(idx);
}

void TemReader::slExit()
{
    m_parseTempr->stopSerial();
    this->close();

    connect(ui->comBaudRate, SIGNAL(currentIndexChanged(int)), SLOT(slBaudRateChange(int)));
    connect(ui->comDataBits, SIGNAL(currentIndexChanged(int)), SLOT(slDataBitsChange(int)));
    connect(ui->comParify, SIGNAL(currentIndexChanged(int)), SLOT(slParifyChange(int)));
    connect(ui->comQueryMode, SIGNAL(currentIndexChanged(int)), SLOT(slQueryModeChange(int)));
    connect(ui->comStopBits, SIGNAL(currentIndexChanged(int)), SLOT(slStopBitsChange(int)));

}

