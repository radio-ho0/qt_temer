#include "temreader.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TemReader w;
    w.show();
    
    return a.exec();
}
