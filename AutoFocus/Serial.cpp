#include "Serial.h"

void Serial::run()
{
	pause_flag = false;		//�߳���ͣ��־ 
	while (!stop_flag)
	{
		if (!pause_flag)
		{
			//int refreshFlag = refresh();h bn
			msleep(50);	//�߳�����1��
		}
	}
	quit();		//�˳��̵߳��¼�ѭ��
}

int Serial::openSerial(QString serialPortName)
{
	int openFlag;
	serialPort.setPortName(serialPortName);
	//�Զ�д��ʽ�򿪴���  
	if (serialPort.open(QIODevice::ReadWrite))
	{
		//���ò�����  
		serialPort.setBaudRate(19200);
		//��������λ  
		serialPort.setDataBits(QSerialPort::Data8);
		//����У��λ  
		serialPort.setParity(QSerialPort::NoParity);
		//����������  
		serialPort.setFlowControl(QSerialPort::NoFlowControl);
		//����ֹͣλ  
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
{	//�رմ���,����ѭ���¼�
	serialPort.close();
	stop_flag = true;
	return 1;
}
