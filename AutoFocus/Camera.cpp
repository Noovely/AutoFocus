/*
2019-5-8 LIUYANG
将对相机和图片的各种操作都放在这儿了吧

2019-1-9 LIUYANG
基于相机的SDK和例程，设计一个方便自己使用的相机类
目前主要用连接相机并获取当前图像，返回其路径
*/
#include "camera.h"
#include <fstream>
#include <iostream>

using namespace std;
using namespace cv;

void cameraDCAM::run()
{
	int flag = 0;
	stop_flag = false;
	pause_flag = true;
	while (!stop_flag)
	{
		if (!pause_flag)
		{
			//获得当前帧图像
			int flag = accessImages(1);
			if (flag)
			{
				cout << "相机获取图像失败，程序结束。" << endl;
				flag = 0;
			}
			else
			{
				cout << "开始了开始了！！！" << endl;
				photoCV = camera2openCV(buf, width, height, rowbytes);
				//photoQImage = Mat2QImage(photoCV);
				emit newPhoto(!flag);
			}
			msleep(80);	//线程休眠0.1秒
		}
	}
	quit();		//退出线程的事件循环
}

int cameraDCAM::cameraConnect()
{
	int successFlag = 0;
	// 初始化DCAM-API并连接设备
	printf("尝试初始化相机......\n");
	hdcam = dcamcon_init_open();
	if (hdcam != NULL)
	{	//成功的话、show device information
		successFlag = 1;		//相机打开成功
		dcamcon_show_dcamdev_info(hdcam);
		
		//打开等待，并返回HDCAMWAIT句柄以供其他dcamwait函数使用。
		DCAMWAIT_OPEN waitopen;
		memset(&waitopen, 0, sizeof(waitopen));
		waitopen.size = sizeof(waitopen);
		waitopen.hdcam = hdcam;
		err = dcamwait_open(&waitopen);
		if (failed(err)){
			dcamcon_show_dcamerr(hdcam, err, "dcamwait_open()");
			successFlag = 2;	//等待句柄打开失败
		}
		else{
			hwait = waitopen.hwait;
			cout << "支持的等待事件:\n" << waitopen.supportevent << endl;
			// 等待设置
			memset(&waitstart, 0, sizeof(waitstart));
			waitstart.size = sizeof(waitstart);
			waitstart.eventmask = DCAMWAIT_CAPEVENT_FRAMEREADY;		//等待事件:准备好从主机软件访问的图像数据
			waitstart.timeout = 1000;

			// 分配内存 捕获缓冲区
			int32 number_of_buffer = 10;			//DCAM将分配的帧数
			err = dcambuf_alloc(hdcam, number_of_buffer);
			if (failed(err)){
				successFlag = 3;	//分配缓冲区失败
				dcamcon_show_dcamerr(hdcam, err, "dcambuf_alloc()");
			}
			else{	// 一切就绪的话……
				cout << "相机初始化 一切就绪！\n" << endl;
			}
		}
	}
	return successFlag;
}

int cameraDCAM::cameraDisconnect(void)
{
	// release buffer
	dcambuf_release(hdcam);
	// close wait handle
	dcamwait_close(hwait);
	// close DCAM handle
	dcamdev_close(hdcam);
	// finalize DCAM-API
	dcamapi_uninit();
	printf("PROGRAM END\n");
	stop_flag = true;
	return 1;
}

int cameraDCAM::accessImages(bool higConFlag)
{
	int errFlag = 0;
	// start capture
	err = dcamcap_start(hdcam, DCAMCAP_START_SEQUENCE);		//不断捕捉图像。如果已使用最后一个缓冲帧，则下一个图像将被复制到第一个缓冲帧
	if (failed(err))
	{
		dcamcon_show_dcamerr(hdcam, err, "dcamcap_start()");
		errFlag = 1;			//开始捕获图像失败
	}		
	else 
	{
		// wait image
		err = dcamwait_start(hwait, &waitstart);
		if (failed(err))
		{
			dcamcon_show_dcamerr(hdcam, err, "dcamwait_start()");
			errFlag = 2;		//开始等待事件失败
			return errFlag;
		}
		// stop capture
		dcamcap_stop(hdcam);
		printf("Capture ...");
		
		//存取图像
		//sample_access_image_with_procoption(hdcam, buf, width, rowbytes, height);		//获取高对比度图像
		// transferinfo param
		DCAMCAP_TRANSFERINFO captransferinfo;
		memset(&captransferinfo, 0, sizeof(captransferinfo));
		captransferinfo.size = sizeof(captransferinfo);
		// get number of captured image
		err = dcamcap_transferinfo(hdcam, &captransferinfo);
		if (failed(err)) {
			dcamcon_show_dcamerr(hdcam, err, "dcamcap_transferinfo()");
			errFlag = 3;		//获取图像传输状态失败
		}
		else {
			if (captransferinfo.nFrameCount < 1) {
				printf("not capture image\n");
				errFlag = 4;		//没捕获到图像
			}
			else {
				//缓冲区设置
				DCAMBUF_FRAME	bufframe;
				memset(&bufframe, 0, sizeof(bufframe));
				bufframe.size = sizeof(bufframe);
				bufframe.iFrame = captransferinfo.nNewestFrameIndex;
				if (higConFlag)
				{	// set proc option
					bufframe.option = DCAMBUF_FRAME_OPTION__PROC_HIGHCONTRAST;
				}
				// access image
				err = dcambuf_lockframe(hdcam, &bufframe);
				if (failed(err))
				{
					dcamcon_show_dcamerr(hdcam, err, "dcambuf_lockframe()");
					errFlag = 5;		//锁定存取图像失败
				}
				else
				{
					//finished
					printf("...Finish!\n");
					width = bufframe.width;
					height = bufframe.height;
					rowbytes = bufframe.rowbytes;
					buf = bufframe.buf;
				}
			}
		}
	}
	return errFlag;
}

cv::Mat camera2openCV(void * buf, long width, long height, long rowbytes)
{	//转换camera缓冲区图像数据为openCV图像Mat类
	ushort *ptrImg = nullptr;
	void *ptrBuf = nullptr;

	Mat img = Mat::ones(height, width, CV_16U);

	if (img.isContinuous())
	{	//整个儿赋值
		ptrImg = img.ptr<ushort>(0);
		ptrBuf = (char*)buf;
		long allbytes = rowbytes * height;
		memcpy_s(ptrImg, allbytes, ptrBuf, allbytes);
	}
	else
	{
		//按行赋值
		for (int row = 0; row < height; row++)
		{

			ptrImg = img.ptr<ushort>(row);
			ptrBuf = (char*)buf + rowbytes * row;

			memcpy_s(ptrImg, rowbytes, ptrBuf, rowbytes);
		}
		cout << endl << "Read image Finish." << endl;
	}
	return img;
}

QImage Mat2QImage(cv::Mat cvImg)
{
	QImage qImg;
		qImg = QImage((const unsigned char*)(cvImg.data),
			cvImg.cols, cvImg.rows,
			cvImg.cols*cvImg.channels(),
			QImage::Format_RGB16);
	
	return qImg;
}

int evaluate_MinMax(cv::Mat imageSource)
{	/*
	//反差式对焦算法
	Mat imageGrey;
	imageGrey = imageSource;
	//cvtColor(imageSource, imageGrey, CV_BGR2GRAY);

	double minVal = 0;
	double maxVal = 0;
	int score;
	minMaxLoc(imageGrey, &minVal, &maxVal);
	score = int(maxVal - minVal);			//评估值忽略低二位的细节值。
	*/
	int score = 1;
	return score;
	
}
