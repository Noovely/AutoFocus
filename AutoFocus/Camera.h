#pragma once
#include <qthread.h>
#include <qimage.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>  
#include "cameraSDK/misc/console4.h"
#include "cameraSDK/misc/common.h"

cv::Mat camera2openCV(void *buf, long width, long height, long rowbytes);          //���ͼ��ת��ΪOpenCV Mat ��ʽ //CV_16U
QImage Mat2QImage(cv::Mat cvImg);
int evaluate_MinMax(cv::Mat imageSource);		////ͼ����������������-�����㷨

//���������������
class cameraDCAM :public QThread
{
	Q_OBJECT
public:
	bool stop_flag = true;		//�߳̽�����־
	bool pause_flag = true;		//�߳���ͣ��־

	//��ȡͼ����Ϣ
	int32 pixeltype;			//
	int32 width = 0;			//ͼ����
	int32 rowbytes = 0;			//ͼ����һ���ֽ���
	int32 height = 0;			//ͼ�����
	void *buf;					//ͼ���׵�ַָ��

	cv::Mat photoCV;			//cv::Mat��ʽʵʱͼ��
	QImage photoQImage;			//QImage��ʽʵʱͼ��

	int cameraConnect();		//�������
	int accessImages(bool highConFlag = 0);		//��ȡͼ��
	int cameraDisconnect();		//�Ͽ����

private:
	DCAMERR err;
	HDCAM hdcam;				//����豸���HDCAM
	HDCAMWAIT hwait;			//�ȴ����HDCAMWAIT
	DCAMWAIT_START waitstart;	//�ȴ���ʼ

protected:
	void run() Q_DECL_OVERRIDE;

signals:
	void newPhoto(int flag);
};
