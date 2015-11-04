#include "video.h"
//#include "ui_widget.h"
#include <QKeyEvent>



#define  UNKNOWN_FLOW_THRESH 1e9

void Widget::keyPressEvent(QKeyEvent *e)
{
    qDebug()<<"haha";
    switch(e->key())
    {


    case Qt::Key_1:
        slot_change_cam();
        break;
    case Qt::Key_2:
        slot_find_line();
        break;
    case Qt::Key_Escape:
            close();
            break;
    }

}

/*void Widget::slot_serial_read()
{
    sp->read_rs=1;
}
void Widget::slot_serial_write()
{
    sp->write_rs=1;
}
void Widget::slot_serial_rx_display()
{
    this->ui->textEdit_2->setText(sp->buf);
}
void Widget::slot_find_line()
{
    if(find_line_flag)
    {
        find_line_flag=false;
    }
    else
    {
        find_line_flag=true;
    }

}*/

Widget::~Widget()
{
    delete ui;
    timer->stop();

    cvReleaseCapture(&pCapture);
    cvReleaseImage(&pImage);
    cvReleaseCapture(&pCapture_2);
    cvReleaseImage(&pImage_2);

}
bool Widget::init()
{
    pImage = NULL;
    pCapture = NULL;
    pCapture_2=NULL;
    pImage_flow = NULL;
    calcing=false;
    if((pCapture = cvCaptureFromCAM(0)) == NULL)
    {
        return false;
    }
    else
    {
        cvSetCaptureProperty(pCapture,CV_CAP_PROP_FPS,60);

    }

    //  if((pCapture_2 = cvCaptureFromCAM(1)) == NULL)
    // {
    //     return false;
    //}
    //else
    // {
    //    cvSetCaptureProperty(pCapture,CV_CAP_PROP_FPS,60);
    // }
    return true;
}
void Widget::slot_change_cam()
{
    static int  cam_index=0;
    if(cam_index==0)
    {
        cam_index=1;
        timer->stop();
        cvReleaseCapture(&pCapture);
        pCapture = cvCaptureFromCAM(1);
        timer->start(1000/60);
    }
    else
    {
        cam_index=0;
        timer->stop();
        cvReleaseCapture(&pCapture);
        pCapture = cvCaptureFromCAM(0);
        timer->start(1000/60);

    }

}



void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    // painter.drawImage(QRect(0,0, 320, 240), image);
    painter.drawImage(QRect(0,0, 640, 480), image_flow);
    //qDebug()<<"paintEvent!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
}

bool Widget::ShowImage()
{
    timer->start(1000/60); // / 24
    cam_date.camera_fps= cvGetCaptureProperty(pCapture,CV_CAP_PROP_FPS);
    QStringList strlist;
    QString str;
    strlist<< "CAM FPS:\t\n";
    strlist<<QString::number(cam_date.camera_fps);
    strlist<< "\t\n";
    str=strlist.join(" ");
    //ui->textEdit->append(str);
    return true;
}



