#pragma once
#include <qthread.h>
#include <qserialport.h>

/*
	����ͨ����
*/

class Serial :public QThread
{
	Q_OBJECT
private:
	QSerialPort serialPort;		//������
	bool stop_flag = true;		//�߳̽�����־
	bool pause_flag = true;		//�߳���ͣ��־

protected:
	void run() Q_DECL_OVERRIDE;

public:
	int openSerial(QString serialPortName);		//�򿪴��ڵĺ���
	int closeSerial();							//�رմ��ں���
	

};

