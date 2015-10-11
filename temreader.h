#ifndef TEMREADER_H
#define TEMREADER_H

#include <QWidget>
#include <QThread>
#include "qextserialport.h"
class parseTempr;
namespace Ui {
class TemReader;
}

class TemReader : public QWidget
{
    Q_OBJECT
    
public:
    explicit TemReader(QWidget *parent = 0);
    ~TemReader();

private:
    Ui::TemReader *ui;

    int isRunning;

    void allConnect();
    PortSettings m_portSettings;
    parseTempr*   m_parseTempr;
    QThread* threadTemp;

private slots:
    void slStartStop();
    void slGetData(QByteArray data);
    void slExit();

    void slBaudRateChange(int idx);
    void slParifyChange(int idx);
    void slDataBitsChange(int idx);
    void slStopBitsChange(int idx);
    void slQueryModeChange(int idx);
    void slChangeTimeout();
    void slGetTargetString(QByteArray data);



};

#endif // TEMREADER_H
