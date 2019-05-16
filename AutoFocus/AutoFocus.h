#pragma once

#include "ui_AutoFocus.h"
#include "Serial.h"
#include "Camera.h"


class AutoFocus : public QMainWindow
{
	Q_OBJECT
public:
	AutoFocus(QWidget *parent = Q_NULLPTR);
	Serial motorSerial;		//����Ĵ���ͨ����
	cameraDCAM camera;		//�����

private:
	QSerialPort serialPort;
	QString serialPortName;
	Ui::AutoFocusClass ui;
	void initUI();

private slots:
	void on_buttonCameraConnect_clicked();		//������Ӱ�ť�ۺ���
	void on_chacekBoxShowImage();				//��ͣʵʱͼ����ʾ�ۺ���				
	void cameraPhoto_show(int flag);			// ��ʾʵʱͼ��ۺ���
	void on_buttonCameraPhoto_clicked();		//������հ�ť�ۺ���
	void on_buttonMotorConnect_clicked();		//������Ӱ�ť�ۺ���
	void on_buttonMotorSet_clicked();			//������Ʋ������òۺ���
	void on_actionFileOpen_triggered();			//�˵������򿪡��ۺ���

protected:
	void closeEvent(QCloseEvent *event);
};
