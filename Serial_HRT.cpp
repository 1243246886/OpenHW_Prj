#include    "Serial_HRT.h"
#include     "mainwindow.h"
#include     <stdio.h>      /*标准输入输出定义*/
#include     <stdlib.h>     /*标准函数库定义*/
#include     <unistd.h>     /*Unix 标准函数定义*/
#include     <sys/types.h>
#include     <sys/stat.h>
#include     "string.h"
#include     <fcntl.h>      /*文件控制定义*/
#include     <termios.h>    /*PPSIX 终端控制定义*/
#include     <errno.h>      /*错误号定义*/
//#define FALSE  -1
//#define TRUE   0
/*********************************************************************/
Serial::Serial()
{

   // unsigned  char *p;
   // p = buff;
    char *dev  = "/dev/ttyUSB0";// /USB串口二
    char *dev_1  = "/dev/ttyUSB1";// /USB串口二
    fd = OpenDev(dev);
    if(-1 == fd)
        fd = OpenDev(dev_1);

    set_speed(fd,9600);	    //bps
    if (set_Parity(fd,8,1,'n') == FALSE)
    {
        printf("Set Parity Error\n");
        exit (0);
    }
    else
    {
        printf("Set Parity success!\n");
    }
}

int Serial::OpenDev(char *Dev)
{
    int fd = open( Dev, O_RDWR/* | O_NOCTTY */ );         //| O_NOCTTY | O_NDELAY
    if (-1 == fd)
    {
        perror("Can't Open Serial Port");
        return -1;
    }
    else
        return fd;
}
/**
*@brief  设置串口通信速率
*@param  fd     类型 int  打开串口的文件句柄
*@param  speed  类型 int  串口速度
*@return  void
*/

void Serial::set_speed(int fd, int speed)
{
    int speed_arr[] = { B38400, B19200, B9600, B4800, B2400, B1200, B57600 };
    int name_arr[] = {38400,  19200,  9600,  4800,  2400,  1200,  57600 };
    int   i;
    int   status;
    struct termios   Opt;
    tcgetattr(fd, &Opt);
    for ( i= 0;  i < sizeof(speed_arr) / sizeof(int);  i++) {
        if  (speed == name_arr[i]) {
            tcflush(fd, TCIOFLUSH);
            cfsetispeed(&Opt, speed_arr[i]);
            cfsetospeed(&Opt, speed_arr[i]);
            status = tcsetattr(fd, TCSANOW, &Opt);
            if  (status != 0) {
                perror("tcsetattr fd1");
                return;
            }
            tcflush(fd,TCIOFLUSH);
        }
    }
}
/**
*@brief   设置串口数据位，停止位和效验位
*@param  fd     类型  int  打开的串口文件句柄
*@param  databits 类型  int 数据位   取值 为 7 或者8
*@param  stopbits 类型  int 停止位   取值为 1 或者2
*@param  parity  类型  int  效验类型 取值为N,E,O,,S
*/
int Serial::set_Parity(int fd,int databits,int stopbits,int parity)
{
    struct termios options;
   // options.c_lflag  &= ~(ICANON | ECHO | ECHOE | ISIG);  /*Input*/
   // options.c_oflag  &= ~OPOST;   /*Output*/
    if  ( tcgetattr( fd,&options)  !=  0) {
        perror("SetupSerial 1");
        return(FALSE);
    }
    options.c_lflag  &= ~(ICANON | ECHO | ECHOE | ISIG);  /*Input*/
    options.c_oflag  &= ~OPOST;   /*Output*/
    options.c_cflag &= ~CSIZE;
    switch (databits) /*设置数据位数*/
    {
    case 7:
        options.c_cflag |= CS7;
        break;
    case 8:
        options.c_cflag |= CS8;
        break;
    default:
        fprintf(stderr,"Unsupported data size/n"); return (FALSE);
    }
    switch (parity)
    {
        case 'n':
        case 'N':
            options.c_cflag &= ~PARENB;   /* Clear parity enable */
            options.c_iflag &= ~INPCK;     /* Enable parity checking */
            break;
        case 'o':
        case 'O':
            options.c_cflag |= (PARODD | PARENB); /* 设置为奇效验*/
            options.c_iflag |= INPCK;             /* Disnable parity checking */
            break;
        case 'e':
        case 'E':
            options.c_cflag |= PARENB;     /* Enable parity */
            options.c_cflag &= ~PARODD;   /* 转换为偶效验*/
            options.c_iflag |= INPCK;       /* Disnable parity checking */
            break;
        case 'S':
        case 's':  /*as no parity*/
            options.c_cflag &= ~PARENB;
            options.c_cflag &= ~CSTOPB;break;
        default:
            fprintf(stderr,"Unsupported parity/n");
            return (FALSE);
    }
    /* 设置停止位*/
    switch (stopbits)
    {
        case 1:
            options.c_cflag &= ~CSTOPB;
            break;
        case 2:
            options.c_cflag |= CSTOPB;
           break;
        default:
             fprintf(stderr,"Unsupported stop bits/n");
             return (FALSE);
    }
    /* Set input parity option */
    if (parity != 'n')
        options.c_iflag |= INPCK;
    tcflush(fd,TCIFLUSH);
    options.c_cc[VTIME] = 6; /* 设置超时15 seconds*/
    options.c_cc[VMIN] =  32 ; /* Update the options and do it NOW */
    if (tcsetattr(fd,TCSANOW,&options) != 0)
    {
        perror("SetupSerial 3");
        return (FALSE);
    }
    return (TRUE);
}
void Serial::stop()
{
    stopped = false;
}
void Serial::run()
{

    int nread;
    //unsigned  char buff[300];
    //int i=0;
    unsigned char flag = '1';
     while (1) //循环读取数据
     {
         while( write(fd, &flag ,1))
         {
            if((nread=read(fd,buff,32))<0)
            {
                printf("read wrong !");
            }
            else
            {
                emit Txd(buff);
                /*printf(" %d\n",nread);
                buff[nread] = '\0';
                for(i=0;i<nread;i++)
                {
                    printf(  " %x", buff[i]);
                }  */
             }
          }
      }

    close(fd);
    //exit (0);
}
