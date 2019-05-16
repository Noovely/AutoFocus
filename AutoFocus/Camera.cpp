/*
2019-5-8 LIUYANG
���������ͼƬ�ĸ��ֲ�������������˰�

2019-1-9 LIUYANG
���������SDK�����̣����һ�������Լ�ʹ�õ������
Ŀǰ��Ҫ�������������ȡ��ǰͼ�񣬷�����·��
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
			//��õ�ǰ֡ͼ��
			int flag = accessImages(1);
			if (flag)
			{
				cout << "�����ȡͼ��ʧ�ܣ����������" << endl;
				flag = 0;
			}
			else
			{
				cout << "��ʼ�˿�ʼ�ˣ�����" << endl;
				photoCV = camera2openCV(buf, width, height, rowbytes);
				//photoQImage = Mat2QImage(photoCV);
				emit newPhoto(!flag);
			}
			msleep(80);	//�߳�����0.1��
		}
	}
	quit();		//�˳��̵߳��¼�ѭ��
}

int cameraDCAM::cameraConnect()
{
	int successFlag = 0;
	// ��ʼ��DCAM-API�������豸
	printf("���Գ�ʼ�����......\n");
	hdcam = dcamcon_init_open();
	if (hdcam != NULL)
	{	//�ɹ��Ļ���show device information
		successFlag = 1;		//����򿪳ɹ�
		dcamcon_show_dcamdev_info(hdcam);
		
		//�򿪵ȴ���������HDCAMWAIT����Թ�����dcamwait����ʹ�á�
		DCAMWAIT_OPEN waitopen;
		memset(&waitopen, 0, sizeof(waitopen));
		waitopen.size = sizeof(waitopen);
		waitopen.hdcam = hdcam;
		err = dcamwait_open(&waitopen);
		if (failed(err)){
			dcamcon_show_dcamerr(hdcam, err, "dcamwait_open()");
			successFlag = 2;	//�ȴ������ʧ��
		}
		else{
			hwait = waitopen.hwait;
			cout << "֧�ֵĵȴ��¼�:\n" << waitopen.supportevent << endl;
			// �ȴ�����
			memset(&waitstart, 0, sizeof(waitstart));
			waitstart.size = sizeof(waitstart);
			waitstart.eventmask = DCAMWAIT_CAPEVENT_FRAMEREADY;		//�ȴ��¼�:׼���ô�����������ʵ�ͼ������
			waitstart.timeout = 1000;

			// �����ڴ� ���񻺳���
			int32 number_of_buffer = 10;			//DCAM�������֡��
			err = dcambuf_alloc(hdcam, number_of_buffer);
			if (failed(err)){
				successFlag = 3;	//���仺����ʧ��
				dcamcon_show_dcamerr(hdcam, err, "dcambuf_alloc()");
			}
			else{	// һ�о����Ļ�����
				cout << "�����ʼ�� һ�о�����\n" << endl;
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
	err = dcamcap_start(hdcam, DCAMCAP_START_SEQUENCE);		//���ϲ�׽ͼ�������ʹ�����һ������֡������һ��ͼ�񽫱����Ƶ���һ������֡
	if (failed(err))
	{
		dcamcon_show_dcamerr(hdcam, err, "dcamcap_start()");
		errFlag = 1;			//��ʼ����ͼ��ʧ��
	}		
	else 
	{
		// wait image
		err = dcamwait_start(hwait, &waitstart);
		if (failed(err))
		{
			dcamcon_show_dcamerr(hdcam, err, "dcamwait_start()");
			errFlag = 2;		//��ʼ�ȴ��¼�ʧ��
			return errFlag;
		}
		// stop capture
		dcamcap_stop(hdcam);
		printf("Capture ...");
		
		//��ȡͼ��
		//sample_access_image_with_procoption(hdcam, buf, width, rowbytes, height);		//��ȡ�߶Աȶ�ͼ��
		// transferinfo param
		DCAMCAP_TRANSFERINFO captransferinfo;
		memset(&captransferinfo, 0, sizeof(captransferinfo));
		captransferinfo.size = sizeof(captransferinfo);
		// get number of captured image
		err = dcamcap_transferinfo(hdcam, &captransferinfo);
		if (failed(err)) {
			dcamcon_show_dcamerr(hdcam, err, "dcamcap_transferinfo()");
			errFlag = 3;		//��ȡͼ����״̬ʧ��
		}
		else {
			if (captransferinfo.nFrameCount < 1) {
				printf("not capture image\n");
				errFlag = 4;		//û����ͼ��
			}
			else {
				//����������
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
					errFlag = 5;		//������ȡͼ��ʧ��
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
{	//ת��camera������ͼ������ΪopenCVͼ��Mat��
	ushort *ptrImg = nullptr;
	void *ptrBuf = nullptr;

	Mat img = Mat::ones(height, width, CV_16U);

	if (img.isContinuous())
	{	//��������ֵ
		ptrImg = img.ptr<ushort>(0);
		ptrBuf = (char*)buf;
		long allbytes = rowbytes * height;
		memcpy_s(ptrImg, allbytes, ptrBuf, allbytes);
	}
	else
	{
		//���и�ֵ
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
	//����ʽ�Խ��㷨
	Mat imageGrey;
	imageGrey = imageSource;
	//cvtColor(imageSource, imageGrey, CV_BGR2GRAY);

	double minVal = 0;
	double maxVal = 0;
	int score;
	minMaxLoc(imageGrey, &minVal, &maxVal);
	score = int(maxVal - minVal);			//����ֵ���ԵͶ�λ��ϸ��ֵ��
	*/
	int score = 1;
	return score;
	
}
