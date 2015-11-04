#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QTimer>
#include <QMainWindow>
#include "qcustomplot.h"
#include"Serial_HRT.h"
#include<qlcdnumber.h>
#include<qslider.h>
#include <cv.h>
#include<highgui.h>
#include<QTimer>
#include<QPixmap>
namespace Ui {
class MainWindow;
}
class Serial;
class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void eg();
    void top();
    void middle();
    void bottom();
    void LCD();
    void slider();
    unsigned char buf[32];
    QCustomPlot *customPlot;
    QCustomPlot *customplot_mid;
    QCustomPlot *customplot_bottom;
    Serial *b;
    QLCDNumber *lcd ; 
   // void setupRealtimeDataDemo(QCustomPlot *customPlot);
protected:
    void keyPressEvent(QKeyEvent *e);
private:
    Ui::MainWindow *ui;
    QString demoName;
    QTimer dataTimer;
    QCPItemTracer *itemDemoPhaseTracer;
    int currentDemoIndex;
    CvCapture *capture ;
    IplImage *frame;
    QTimer *timer1;
private slots:
    void close_slot();
    void realtimeDataSlot();
    void RXD(unsigned char *rxd);
    void getFrame();
};

#endif // MAINWINDOW_H
