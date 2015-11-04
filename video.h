#ifndef VIDEO_H
#define VIDEO_H
#include <QWidget>
#include <QImage>
#include <QTimer>
#include <QDebug>
#include <QPainter>
#include <QVector>
#include <QThread>

#include <stdio.h>
#include <cstring>
//#include "serial.h"
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/video/tracking.hpp"
//#include "img_deal.h"


using namespace std;
using namespace cv;

struct CAM_DATE
{
    double camera_fps;
};

namespace Ui {     //Qt shiyong jicheng de fangshi shiyong designer chuangjande chuangti
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:

    double Tick_t;
    CAM_DATE cam_date;

    explicit Widget(QWidget *parent = 0);
    ~Widget();
    bool ShowImage();
    bool init();
    void makecolorwheel(vector<Scalar> &colorwheel);
    void motionToColor(Mat flow, Mat &color);

protected:
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *e);

private:
    //serial *sp;
    Ui::Widget *ui;
    QImage image;
    QImage image_flow;
    QTimer *timer;
    IplImage *pImage;
    IplImage *pImage_2;
    IplImage *pImage_flow;
    CvCapture *pCapture;
    CvCapture *pCapture_2;
    Mat prevgray,flow,cflow,frame,gray_end;
    Mat motion2color;
    Mat one_frame;
    Mat one_frame_thr;
    Mat one_frame_out;
    bool calcing;
    //IMG_DEAL  img_deal;
    bool find_line_flag;

public slots:
    void slot_find_line();
    void slot_change_cam();
    //void slot_serial_write();
    //void slot_serial_read();
   // void slot_serial_rx_display();
    void slot_timer_positionImage();

private slots:
    void on_writepb_clicked();
};
#endif // VIDEO_H
