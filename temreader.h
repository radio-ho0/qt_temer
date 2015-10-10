#ifndef TEMREADER_H
#define TEMREADER_H

#include <QWidget>

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
};

#endif // TEMREADER_H
