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

    enum TEMPER_PROPERTY{
        HEADER_OFFSET,
        HI_TEMP_OFFSET,
        HUMIDITY_OFFSET,
        TEMP_OFFSET,
        TEMPF_OFFSET,

        THE_END
    };

signals:
    void sendHiTemp(double temp);
    void sendTemp(double temp);
    void sendTempc(double tempc);
    void sendHumi(double humi);
    void sendHeatIndex1(double index1);
    void sendHeatIndex2(double index2);
    void sendData(QByteArray data);

    void sendTargetStr(QByteArray data);
public slots:

    void start(const QString& portName, const PortSettings &settings, QextSerialPort::QueryMode mode = QextSerialPort::EventDriven);
    void stopSerial();

private:
    QextSerialPort* port;

private slots:
    void slRead();
    void doParse(QByteArray data);


};

#endif // PARSETEMPR_H
