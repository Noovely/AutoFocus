#pragma once
#include <qthread.h>
#include <qimage.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>  
#include "cameraSDK/misc/console4.h"
#include "cameraSDK/misc/common.h"

cv::Mat camera2openCV(void *buf, long width, long height, long rowbytes);          //相机图像转换为OpenCV Mat 格式 //CV_16U
QImage Mat2QImage(cv::Mat cvImg);
int evaluate_MinMax(cv::Mat imageSource);		////图像清晰度评估函数-反差算法

//操作滨松相机的类
class cameraDCAM :public QThread
{
	Q_OBJECT
public:
	bool stop_flag = true;		//线程结束标志
	bool pause_flag = true;		//线程暂停标志

	//获取图像信息
	int32 pixeltype;			//
	int32 width = 0;			//图像宽度
	int32 rowbytes = 0;			//图像下一行字节数
	int32 height = 0;			//图像告诉
	void *buf;					//图像首地址指针

	cv::Mat photoCV;			//cv::Mat格式实时图像
	QImage photoQImage;			//QImage格式实时图像

	int cameraConnect();		//连接相机
	int accessImages(bool highConFlag = 0);		//获取图像
	int cameraDisconnect();		//断开相机

private:
	DCAMERR err;
	HDCAM hdcam;				//相机设备句柄HDCAM
	HDCAMWAIT hwait;			//等待句柄HDCAMWAIT
	DCAMWAIT_START waitstart;	//等待开始

protected:
	void run() Q_DECL_OVERRIDE;

signals:
	void newPhoto(int flag);
};
