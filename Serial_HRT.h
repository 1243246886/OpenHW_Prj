#ifndef SERIAL_HRT_H
#define SERIAL_HRT_H
#include<QThread>
#include <QObject>
class Serial:public QThread
{
  Q_OBJECT
 public:
  Serial();
  int OpenDev(char *Dev);
  void set_speed(int fd, int speed);
  int set_Parity(int fd,int databits,int stopbits,int parity);
  //----------------------------------------------------------------//
  unsigned char buff[32];
  int fd;
  void stop();
  volatile bool stopped;
protected:
  virtual void run();
signals:
  void Txd(unsigned char *txd);
};
#endif // SERIAL_HRT_H
