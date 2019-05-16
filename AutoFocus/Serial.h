#pragma once
#include <qthread.h>
#include <qserialport.h>

/*
	串口通信类
*/

class Serial :public QThread
{
	Q_OBJECT
private:
	QSerialPort serialPort;		//串口类
	bool stop_flag = true;		//线程结束标志
	bool pause_flag = true;		//线程暂停标志

protected:
	void run() Q_DECL_OVERRIDE;

public:
	int openSerial(QString serialPortName);		//打开串口的函数
	int closeSerial();							//关闭串口函数
	

};

