#include <QtGui/QApplication>
#include "mainwindow.h"
#include "Serial_HRT.h"

//#include "qcustomplot.h"
// static
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.showFullScreen();

    return a.exec();
}
