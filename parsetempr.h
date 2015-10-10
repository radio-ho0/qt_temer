#ifndef PARSETEMPR_H
#define PARSETEMPR_H
#include "qextserialport.h"

#include <QObject>
class QextSerialPort;
class parseTempr : public QObject
{
    Q_OBJECT
public:
    explicit parseTempr(QObject *parent = 0);
    ~parseTempr();

signals:
    void sendHiTemp(double temp);
    void sendTemp(double temp);
    void sendHumi(double humi);
    void sendHeatIndex1(double index1);
    void sendHeatIndex2(double index2);
    void sendData(QByteArray data);
public slots:

    void start(const QString& portName, const PortSettings &settings, QextSerialPort::QueryMode mode = QextSerialPort::EventDriven);
    void stopSerial();

private:
    QextSerialPort* port;

private slots:
    void slRead();


};

#endif // PARSETEMPR_H
