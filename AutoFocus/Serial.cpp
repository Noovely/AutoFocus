#include "Serial.h"

void Serial::run()
{
	pause_flag = false;		//线程暂停标志 
	while (!stop_flag)
	{
		if (!pause_flag)
		{
			//int refreshFlag = refresh();h bn
			msleep(50);	//线程休眠1秒
		}
	}
	quit();		//退出线程的事件循环
}

int Serial::openSerial(QString serialPortName)
{
	int openFlag;
	serialPort.setPortName(serialPortName);
	//以读写方式打开串口  
	if (serialPort.open(QIODevice::ReadWrite))
	{
		//设置波特率  
		serialPort.setBaudRate(19200);
		//设置数据位  
		serialPort.setDataBits(QSerialPort::Data8);
		//设置校验位  
		serialPort.setParity(QSerialPort::NoParity);
		//设置流控制  
		serialPort.setFlowControl(QSerialPort::NoFlowControl);
		//设置停止位  
		serialPort.setStopBits(QSerialPort::OneStop);
		stop_flag = false;
		openFlag = 1;
	}
	else
	{
		stop_flag = true;
		openFlag = 0;
	}
	return openFlag;
}

int Serial::closeSerial()
{	//关闭串口,结束循环事件
	serialPort.close();
	stop_flag = true;
	return 1;
}
