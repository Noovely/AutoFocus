/*
	AutoFocus 2.0
	2019.05.07 LiuYang
*/

#pragma execution_character_set("utf-8")

#include "AutoFocus.h"
#include <qserialportinfo.h>
#include <qmessagebox.h>
#include <qevent.h>
#include <qdebug.h>
#include <qdatetime.h>
#include <qfiledialog.h>
#include <ctime>

using namespace cv;

AutoFocus::AutoFocus(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	initUI();
}

void AutoFocus::initUI()
{
	connect(&camera, SIGNAL(newPhoto(int)), this, SLOT(cameraPhoto_show(int))); 
	connect(ui.checkBoxShowImage, SIGNAL(clicked()), this, SLOT(on_chacekBoxShowImage()));

	//初始化串口下拉菜单列表
	ui.comMotorCom->clear();
	foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
		qDebug() << "Name:" << info.portName();
		qDebug() << "Description:" << info.description();
		qDebug() << "Manufacturer:" << info.manufacturer() << "\n";
		ui.comMotorCom->addItem(info.portName());
	}
	ui.statusBar->showMessage(tr("就绪").arg(serialPortName),10000);
}

void AutoFocus::on_buttonCameraConnect_clicked() {
	//连接相机按钮槽函数
	if (ui.buttonCameraConnect->text() == "\350\277\236\346\216\245")
	{
		int connectFlag = camera.cameraConnect();
		if (connectFlag) {
			ui.buttonCameraPhoto->setEnabled(true);
			ui.buttonCameraPath->setEnabled(true);
			ui.lineEditCameraPath->setEnabled(true);
			ui.checkBoxShowImage->setEnabled(true);
			ui.checkBoxHighContrast->setEnabled(true);
			ui.buttonCameraConnect->setText(QApplication::translate("LIDARClass", "\346\226\255\345\274\200", nullptr));		//设为“断开”
			camera.start();			//开始子线程
			ui.statusBar->showMessage(tr("相机已连接"), 5000);
		}
		else {
			qDebug() << "连接相机失败,程序结束。" << endl;
			ui.statusBar->showMessage(tr("相机连接失败"), 5000);
			QMessageBox::critical(this, "提示", "相机端口打开失败");
		}
	}
	else if (ui.buttonCameraConnect->text() == "\346\226\255\345\274\200")
	{
		camera.exit();
		int closeFlag = camera.cameraDisconnect();
		if (closeFlag)
		{
			//结束子线程
			if (camera.isRunning()) {
				camera.stop_flag = true;
				camera.wait();
			}
			//界面组件使不能
			ui.buttonCameraPhoto->setEnabled(false);
			ui.buttonCameraPath->setEnabled(false);
			ui.lineEditCameraPath->setEnabled(false);
			ui.checkBoxShowImage->setEnabled(false);
			ui.checkBoxHighContrast->setEnabled(false);
			ui.buttonCameraConnect->setText(QApplication::translate("LIDARClass", "\350\277\236\346\216\245", nullptr));		//设为“连接”
			QMessageBox::information(this, "提示", "相机连接已断开");
		}
	}
}


void AutoFocus::on_chacekBoxShowImage()
{	//显示实时图像槽函数
	if (ui.checkBoxShowImage->isChecked()) {
		camera.pause_flag = false;
		//camera.stop_flag = false;
		cv::namedWindow("Live", cv::WINDOW_GUI_NORMAL);  // 创建窗口
	}
	else {
		camera.pause_flag = true;
	}
}

void AutoFocus::cameraPhoto_show(int flag)
{	//信号响应-相机帧实时显示
	//ui.labelImage->setPixmap(QPixmap::fromImage(camera.photoQImage));
	cv::Mat imageShow;
	camera.photoCV.convertTo(imageShow, CV_8U, 1.0 / 256);
	imshow("Live", imageShow);
	cv::waitKey(2);	//键盘按任意键，关闭。
}

void AutoFocus::on_buttonCameraPhoto_clicked()
{	//拍照按钮槽函数
	QDateTime curDateTime = QDateTime::currentDateTime();
	//const char* fileName = "Resources/image/img"+curDateTime.toString("yyyyMMddhhmmss")+".tif";
	cv::String filePath = "Resources/image/img.tif";
	if (camera.isRunning() && ui.checkBoxShowImage->isChecked())
	{
		cv::imwrite(filePath, camera.photoCV);
		//output_data(fileName, (char *)camera.buf, camera.width* 2 * camera.height);
		ui.statusBar->showMessage(tr("照片已保存至 ../Resources/image/img.tif"), 5000);
	}
	else
	{	//获得当前帧图像
		int flag = camera.accessImages(ui.checkBoxHighContrast->isChecked());
		if (flag)
		{
			qDebug() << "相机获取图像失败，错误代码" << flag << endl;
			QMessageBox::critical(this, "提示", "相机获取图像失败");
		}
		else
		{
			cv::namedWindow("AutoFocusing", cv::WINDOW_GUI_NORMAL);  // 创建窗口
			cv::Mat img = camera2openCV(camera.buf, camera.width, camera.height, camera.rowbytes);
			cv::imwrite("Resources/image/imgB.tif",img);
			ui.statusBar->showMessage(tr("照片已保存至 ../Resources/image/imgB.tif"), 5000);
			img.convertTo(img, CV_8U, 1.0 / 256);
			imshow("AutoFocusing", img);
			cv::waitKey(0);	//键盘按任意键，关闭。
		}
	}
}

void AutoFocus::on_buttonMotorConnect_clicked()
{	//连接电机按钮槽函数
	if (ui.buttonMotorConnect->text() == "\350\277\236\346\216\245")
	{
		//设置串口号  
		serialPortName = ui.comMotorCom->currentText();
		int openFlag = motorSerial.openSerial(serialPortName);
		if (openFlag)
		{
			//界面组件使能
			ui.spinMotorAdress->setEnabled(true);
			ui.spinMotorDirction->setEnabled(true);
			ui.spinMotorSpeed->setEnabled(true);
			ui.spinMotorStep->setEnabled(true);
			ui.buttonMotorSet->setEnabled(true);
			ui.buttonMotorLeft->setEnabled(true);
			ui.buttonMotorRight->setEnabled(true);

			//改变连接按钮	
			ui.comMotorCom->setEnabled(false);
			ui.buttonMotorConnect->setText(QApplication::translate("LIDARClass", "\346\226\255\345\274\200", nullptr));		//设为“断开”
			ui.statusBar->showMessage(tr("控制电机端口%1连接成功").arg(serialPortName), 3000);
		}
		else
		{
			qDebug() << QObject::tr("Failed to open port %1, error: %2")
				.arg(serialPortName).arg(serialPort.errorString())
				<< endl;
			ui.statusBar->showMessage(tr("控制电机端口%1连接失败").arg(serialPortName), 5000);
			QMessageBox::critical(this, "提示", "控制电机端口打开失败");
		}
	}
	else if (ui.buttonMotorConnect->text() == "\346\226\255\345\274\200")
	{
		int closeFlag = motorSerial.closeSerial();
		if (closeFlag)
		{
			//界面组件使不能
			ui.spinMotorAdress->setEnabled(false);
			ui.spinMotorDirction->setEnabled(false);
			ui.spinMotorSpeed->setEnabled(false);
			ui.spinMotorStep->setEnabled(false);
			ui.buttonMotorSet->setEnabled(false);
			ui.buttonMotorLeft->setEnabled(false);
			ui.buttonMotorRight->setEnabled(false);
			ui.comMotorCom->setEnabled(true);
			ui.buttonMotorConnect->setText(QApplication::translate("LIDARClass", "\350\277\236\346\216\245", nullptr));		//设为“连接”
			ui.statusBar->showMessage(tr("控制电机端口已关闭").arg(serialPortName), 5000);
			QMessageBox::information(this, "提示", "控制电机端口已关闭");
		}
	}
	else {
		ui.buttonMotorConnect->setText(QApplication::translate("LIDARClass", "\350\277\236\346\216\245", nullptr));		//设为“连接”
		QMessageBox::information(this, "提示", "控制电机端口已关闭");
	}
}

void AutoFocus::on_buttonMotorSet_clicked()
{	//电机控制参数设置槽函数
	char timev[100];
	tm* localTime;
	time_t timep = time(NULL);
	localTime = localtime(&timep); //转为本地时间  
	strftime(timev, 64, "%Y%m%d%H%M%S", localTime);
	std::cout << "time():" << timev << std::endl;
}

void AutoFocus::on_actionFileOpen_triggered()
{	//菜单栏“打开”槽函数
	QString curPath = QDir::currentPath();	//获取应用程序当前目录
	QString dlgTitle = "打开文件";
	QString filter = "图像文件(*.tif *.jpg *.png *.bmp *.raw);;所有文件(*.*)";
	QString aFileName = QFileDialog::getOpenFileName(this, dlgTitle, curPath, filter);
	qDebug() << aFileName << endl;
}

void AutoFocus::closeEvent(QCloseEvent * event)
{	//重写窗口关闭事件，必须结束线程
	if (camera.isRunning())
	{
		camera.cameraDisconnect();
		camera.wait();
	}
	event->accept();
}
