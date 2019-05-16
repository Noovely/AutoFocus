#pragma once

#include "ui_AutoFocus.h"
#include "Serial.h"
#include "Camera.h"


class AutoFocus : public QMainWindow
{
	Q_OBJECT
public:
	AutoFocus(QWidget *parent = Q_NULLPTR);
	Serial motorSerial;		//电机的串口通信类
	cameraDCAM camera;		//相机类

private:
	QSerialPort serialPort;
	QString serialPortName;
	Ui::AutoFocusClass ui;
	void initUI();

private slots:
	void on_buttonCameraConnect_clicked();		//相机连接按钮槽函数
	void on_chacekBoxShowImage();				//启停实时图像显示槽函数				
	void cameraPhoto_show(int flag);			// 显示实时图像槽函数
	void on_buttonCameraPhoto_clicked();		//相机拍照按钮槽函数
	void on_buttonMotorConnect_clicked();		//电机连接按钮槽函数
	void on_buttonMotorSet_clicked();			//电机控制参数设置槽函数
	void on_actionFileOpen_triggered();			//菜单栏“打开”槽函数

protected:
	void closeEvent(QCloseEvent *event);
};
