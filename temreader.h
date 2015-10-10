#ifndef TEMREADER_H
#define TEMREADER_H

#include <QWidget>
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

private slots:
    void slStartStop();
    void slGetData(QByteArray data);
    void slChangeTimeout();
    void slExit();
    void slPortChange();



};

#endif // TEMREADER_H
