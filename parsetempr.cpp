#include "parsetempr.h"
#include "qextserialport.h"
#include <QDebug>
parseTempr::parseTempr(QObject *parent) :
    QObject(parent)
{

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
    }
}
