#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qcustomplot.h"
#include <QVector>
#include<QHBoxLayout>
#include"Serial_HRT.h"
void MainWindow::keyPressEvent(QKeyEvent *e)
{
    switch(e->key())
    {
    case Qt::Key_Escape:
        close();
        break;
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //--------------------------------------------------------//
    timer1 = new QTimer(this);
    capture = cvCaptureFromCAM(-1);
    //timer->start(33);
    if(capture == NULL)
    {
      qDebug()<<"esrror";
    }
    timer1->start(50);
    connect(timer1,SIGNAL(timeout()),this,SLOT(getFrame()));
    //-------------------------------------------------------//
    b = new Serial();
    //eg();
    top();
    middle();
    bottom();
    LCD();
    QObject::connect(b,SIGNAL(Txd(unsigned char *)),this,SLOT(RXD(unsigned char *)));
   // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
    QObject::connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
    QObject::connect(this->ui->pb_close,SIGNAL(clicked()),this,SLOT(close_slot()));
   // second thread to receive serial message.
    b->start();

//---------------------------------------------------------------------for layout---------------------------------------------------//
   /*QGridLayout *rightlayout = new QGridLayout;
    rightlayout->addWidget(customplot_eg,0,0);
    rightlayout->addWidget(customPlot,0,1);

    QHBoxLayout *mainlayout = new QHBoxLayout;
    mainlayout->addLayout(rightlayout);*/
//----------------------------------------------------------------------------------------------------------------------------------//
}
void MainWindow::close_slot()
{
    close();
}

void MainWindow::RXD(unsigned char *rxd)
{
    for (int i=0;i<32;i++)
        buf[i] = rxd[i] ;
}
void MainWindow::getFrame()
{
    frame = cvQueryFrame(capture);
    QImage image = QImage((const uchar*)frame->imageData,frame->width,frame->height,QImage::Format_RGB888).rgbSwapped();
   this->ui->label->setPixmap(QPixmap::fromImage(image));
}
void MainWindow::top()
{
    //--------------------------------------------------------------------------------------------------------------------------//

        customPlot = new QCustomPlot(this);
        // include this section to fully disable antialiasing for higher performance:   
        /* customplot_eg->setNotAntialiasedElements(QCP::aeAll);
        QFont font;
        font.setStyleStrategy(QFont::NoAntialias);
        customplot_eg->xAxis->setTickLabelFont(font);
        customplot_eg->yAxis->setTickLabelFont(font);
        customplot_eg->legend->setFont(font); */
        //customPlot-> resize(0,40);
        customPlot->legend->setVisible(true);
        customPlot->legend->setFont(QFont("Helvetica",9));
        customPlot->setGeometry(400, 0, 624, 200);
        customPlot->addGraph(); // blue line
        customPlot->graph(0)->setPen(QPen(Qt::blue));
        customPlot->graph(0)->setBrush(QBrush(QColor(240, 255, 200)));
        customPlot->graph(0)->setAntialiasedFill(false);
        customPlot->addGraph(); // red line
        customPlot->graph(1)->setPen(QPen(Qt::red));
        customPlot->graph(0)->setChannelFillGraph(customPlot->graph(1));
        customPlot->graph(0)->setName("haha");

        customPlot->addGraph(); // blue dot
        customPlot->graph(2)->setPen(QPen(Qt::blue));
        customPlot->graph(2)->setLineStyle(QCPGraph::lsNone);
        customPlot->graph(2)->setScatterStyle(QCPScatterStyle::ssDisc);
        customPlot->addGraph(); // red dot
        customPlot->graph(3)->setPen(QPen(Qt::red));
        customPlot->graph(3)->setLineStyle(QCPGraph::lsNone);
        customPlot->graph(3)->setScatterStyle(QCPScatterStyle::ssDisc);

        customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);   //set the time style on X ;
        customPlot->xAxis->setDateTimeFormat("hh:mm:ss");
        customPlot->xAxis->setAutoTickStep(false);
        customPlot->xAxis->setTickStep(1);                          // 1S shijian fenduzhi
       // customPlot->xAxis->setTickLabelRotation(30);

        customPlot->axisRect()->setupFullAxesBox();
        // make left and bottom axes transfer their ranges to right and top axes:
        connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
        connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));
        dataTimer.start(0); // Interval 0 means to refresh as fast as possible



}
void MainWindow::middle()
{
    //--------------------------------------------------------------------------------------------------------------------------//

        customplot_mid = new QCustomPlot(this);

        customplot_mid->setGeometry(400, 180, 624, 200);
        customplot_mid->addGraph(); // blue line
        customplot_mid->graph(0)->setPen(QPen(Qt::blue));
        customplot_mid->graph(0)->setBrush(QBrush(QColor(240, 255, 200)));
        customplot_mid->graph(0)->setAntialiasedFill(false);
        customplot_mid->addGraph(); // red line
        customplot_mid->graph(1)->setPen(QPen(Qt::red));
        customplot_mid->graph(0)->setChannelFillGraph(customplot_mid->graph(1));

        customplot_mid->addGraph(); // blue dot
        customplot_mid->graph(2)->setPen(QPen(Qt::blue));
        customplot_mid->graph(2)->setLineStyle(QCPGraph::lsNone);
        customplot_mid->graph(2)->setScatterStyle(QCPScatterStyle::ssDisc);
        customplot_mid->addGraph(); // red dot
        customplot_mid->graph(3)->setPen(QPen(Qt::red));
        customplot_mid->graph(3)->setLineStyle(QCPGraph::lsNone);
        customplot_mid->graph(3)->setScatterStyle(QCPScatterStyle::ssDisc);

        customplot_mid->xAxis->setTickLabelType(QCPAxis::ltDateTime);   //set the time style on X ;
        customplot_mid->xAxis->setDateTimeFormat("hh:mm:ss");
        customplot_mid->xAxis->setAutoTickStep(false);
        customplot_mid->xAxis->setTickStep(1);                          // 1S shijian fenduzhi
                               // 1S shijian fenduzhi
        customplot_mid->xAxis->setTickLabelRotation(30);
        customplot_mid->axisRect()->setupFullAxesBox();
        // make left and bottom axes transfer their ranges to right and top axes:
        connect(customplot_mid->xAxis, SIGNAL(rangeChanged(QCPRange)), customplot_mid->xAxis2, SLOT(setRange(QCPRange)));
        connect(customplot_mid->yAxis, SIGNAL(rangeChanged(QCPRange)), customplot_mid->yAxis2, SLOT(setRange(QCPRange)));
        dataTimer.start(0); // Interval 0 means to refresh as fast as possible



}
void MainWindow::bottom()
{
    //--------------------------------------------------------------------------------------------------------------------------//

        customplot_bottom = new QCustomPlot(this);

        customplot_bottom->setGeometry(0, 375, 1024, 200);
        customplot_bottom->addGraph(); // blue line
        customplot_bottom->graph(0)->setPen(QPen(Qt::blue));
        customplot_bottom->graph(0)->setBrush(QBrush(QColor(240, 255, 200)));
        customplot_bottom->graph(0)->setAntialiasedFill(false);
        customplot_bottom->addGraph(); // red line
        customplot_bottom->graph(1)->setPen(QPen(Qt::red));
        customplot_bottom->graph(0)->setChannelFillGraph(customplot_bottom->graph(1));

        customplot_bottom->addGraph(); // blue dot
        customplot_bottom->graph(2)->setPen(QPen(Qt::blue));
        customplot_bottom->graph(2)->setLineStyle(QCPGraph::lsNone);
        customplot_bottom->graph(2)->setScatterStyle(QCPScatterStyle::ssDisc);
        customplot_bottom->addGraph(); // red dot
        customplot_bottom->graph(3)->setPen(QPen(Qt::red));
        customplot_bottom->graph(3)->setLineStyle(QCPGraph::lsNone);
        customplot_bottom->graph(3)->setScatterStyle(QCPScatterStyle::ssDisc);

        customplot_bottom->xAxis->setTickLabelType(QCPAxis::ltDateTime);   //set the time style on X ;
        customplot_bottom->xAxis->setDateTimeFormat("hh:mm:ss");
        customplot_bottom->xAxis->setAutoTickStep(false);
        customplot_bottom->xAxis->setTickStep(1);                          // 1S shijian fenduzhi
        customplot_bottom->axisRect()->setupFullAxesBox();
        customplot_bottom->xAxis->setTickLabelRotation(30);
        // make left and bottom axes transfer their ranges to right and top axes:
        connect(customplot_bottom->xAxis, SIGNAL(rangeChanged(QCPRange)), customplot_bottom->xAxis2, SLOT(setRange(QCPRange)));
        connect(customplot_bottom->yAxis, SIGNAL(rangeChanged(QCPRange)), customplot_bottom->yAxis2, SLOT(setRange(QCPRange)));
        dataTimer.start(0); // Interval 0 means to refresh as fast as possible



}
int i;
void MainWindow::realtimeDataSlot()
{
  // calculate two new data points:
#if QT_VERSION < QT_VERSION_CHECK(4, 7, 0)
  double key = 0;
#else
  double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
#endif

  static double lastPointKey = 0;
  if (key-lastPointKey > 0.01) // at most add point every 10 ms
  {
      i ++;
      if(i == 31)
          i =0;
   // Date
      double value0 =  buf[4];
      double value1 =  buf[5];
      double value2 =  buf[2]*256 +buf[3];
      double value3 =  buf[2]*256 +buf[3];
      double value4 =  buf[0]*256 + buf[1];   //right shift >> can improve the speed but the buf[] need int type.
      double value5 =  buf[0]*256 + buf[1];
    //add data to LCD
      lcd->display(99);
    // add data to progressBar
      ui->progressBar->setValue(90);
    // add data to lines:
    customPlot->graph(0)->addData(key, value0);
    customPlot->graph(1)->addData(key, value1);
       //----middle
    customplot_mid->graph(0)->addData(key, value2);
    customplot_mid->graph(1)->addData(key, value3);
      //-----bottom
    customplot_bottom->graph(0)->addData(key, value4);
    customplot_bottom->graph(1)->addData(key, value5);

    // set data of dots:
    customPlot->graph(2)->clearData();
    customPlot->graph(2)->addData(key, value0);
    customPlot->graph(3)->clearData();
    customPlot->graph(3)->addData(key, value1);
    //middle
    customplot_mid->graph(2)->clearData();
    customplot_mid->graph(2)->addData(key, value2);
    customplot_mid->graph(3)->clearData();
    customplot_mid->graph(3)->addData(key, value3);
    //bottom
    customplot_bottom->graph(2)->clearData();
    customplot_bottom->graph(2)->addData(key, value4);
    customplot_bottom->graph(3)->clearData();
    customplot_bottom->graph(3)->addData(key, value5);

    // remove data of lines that's outside visible range:
    customPlot->graph(0)->removeDataBefore(key-8);
    customPlot->graph(1)->removeDataBefore(key-8);
    //middle
    customplot_mid->graph(0)->removeDataBefore(key-8);
    customplot_mid->graph(1)->removeDataBefore(key-8);
    //bottom
    customplot_bottom->graph(0)->removeDataBefore(key-8);
    customplot_bottom->graph(1)->removeDataBefore(key-8);

    // rescale value (vertical) axis to fit the current data:
    customPlot->graph(0)->rescaleValueAxis();
    customPlot->graph(1)->rescaleValueAxis(true);
    //middle
    customplot_mid->graph(0)->rescaleValueAxis();
    customplot_mid->graph(1)->rescaleValueAxis(true);
    //bottom
    customplot_bottom->graph(0)->rescaleValueAxis();
    customplot_bottom->graph(1)->rescaleValueAxis(true);

    lastPointKey = key;
  }
  // make key axis range scroll with the data (at a constant range size of 8):
  customPlot->xAxis->setRange(key+0.25, 8, Qt::AlignRight);
  customPlot->replot();
  customplot_mid->xAxis->setRange(key+0.25, 8, Qt::AlignRight);
  customplot_mid->replot();
  customplot_bottom->xAxis->setRange(key+0.25, 8, Qt::AlignRight);
  customplot_bottom->replot();
  // calculate frames per second:
  static double lastFpsKey;
  static int frameCount;
  ++frameCount;
  if (key-lastFpsKey > 2) // average fps over 2 seconds
  {
    ui->statusBar->showMessage(
          QString("%1 FPS, Total Data points: %2")
          .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
          .arg(customPlot->graph(0)->data()->count()+customPlot->graph(1)->data()->count())
          , 0);
    lastFpsKey = key;
    frameCount = 0;
  }
}

// Add the wideget

void MainWindow::LCD()
{
    lcd = new QLCDNumber(2,this);
    lcd->setGeometry(0,575,190,193);
    lcd->display(20);
}

void MainWindow::eg()
{
    QCustomPlot *customplot_eg = new QCustomPlot(this);

    customplot_eg->setGeometry(0, 370, 1366, 200);

    QVector<double> x (1010);
    QVector<double> y (1010);

    for(int i=0; i<1010;i++)
    {
        x[i]=i;
        y[i]=x[i];
    }

    customplot_eg->addGraph();
    customplot_eg->graph()->setData(x,y);
   // customplot_eg->xAxis->setLabel("X");
   // customplot_eg->yAxis->setLabel("y");
    customplot_eg->xAxis->setRange(0,1000);
    customplot_eg->yAxis->setRange(0,1000);
}

MainWindow::~MainWindow()
{
    timer1->stop();
    cvReleaseCapture(&capture);
    delete ui;
}
