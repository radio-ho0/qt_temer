#include "parsetempr.h"
#include "qextserialport.h"
#include <QRegExp>
#include <QStringList>
#include <QDebug>

const char* headerStr = "EMPER";
parseTempr::parseTempr(QObject *parent) :
    QObject(parent)
{
    port = NULL;
}

parseTempr::~parseTempr()
{
    if(port != NULL){
        delete port;
        port = NULL;
    }

}

void parseTempr::start(const QString &portName, const PortSettings &settings, QextSerialPort::QueryMode mode)
{
    port = new QextSerialPort(portName, settings, mode);
    port->open(QIODevice::ReadWrite);
    connect(port, SIGNAL(readyRead()), SLOT(slRead()));

    qDebug() << "is running " << port->isOpen() << endl;

}

void parseTempr::stopSerial()
{
    if(port != NULL){
        port->close();
        delete port;
        port = NULL;
    }
}

void parseTempr::slRead()
{
    if (port->bytesAvailable()) {
        QByteArray data = port->readAll();
        emit sendData(data);
        doParse(data);
    }
}

void parseTempr::doParse(QByteArray data)
{
    if(data.contains(headerStr)){
//        QStringList list = QString::fromUtf8(data).split(',');
//        double hiTemp = list.at(HI_TEMP_OFFSET).toDouble();
//        double humidity = list.at(HUMIDITY_OFFSET).toDouble();
//        double temp = list.at(TEMP_OFFSET).toDouble();
//        double tempf = list.at(TEMPF_OFFSET).toDouble();

//        emit sendHiTemp(hiTemp);
//        emit sendHumi(humidity);
//        emit sendTemp(temp);
//        emit sendTempc(tempf);
//        qDebug() << list  << "1" << list.at(1) << endl;

        emit sendTargetStr(data);
    }

}
