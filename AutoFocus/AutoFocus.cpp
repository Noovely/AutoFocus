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

	//��ʼ�����������˵��б�
	ui.comMotorCom->clear();
	foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
		qDebug() << "Name:" << info.portName();
		qDebug() << "Description:" << info.description();
		qDebug() << "Manufacturer:" << info.manufacturer() << "\n";
		ui.comMotorCom->addItem(info.portName());
	}
	ui.statusBar->showMessage(tr("����").arg(serialPortName),10000);
}

void AutoFocus::on_buttonCameraConnect_clicked() {
	//���������ť�ۺ���
	if (ui.buttonCameraConnect->text() == "\350\277\236\346\216\245")
	{
		int connectFlag = camera.cameraConnect();
		if (connectFlag) {
			ui.buttonCameraPhoto->setEnabled(true);
			ui.buttonCameraPath->setEnabled(true);
			ui.lineEditCameraPath->setEnabled(true);
			ui.checkBoxShowImage->setEnabled(true);
			ui.checkBoxHighContrast->setEnabled(true);
			ui.buttonCameraConnect->setText(QApplication::translate("LIDARClass", "\346\226\255\345\274\200", nullptr));		//��Ϊ���Ͽ���
			camera.start();			//��ʼ���߳�
			ui.statusBar->showMessage(tr("���������"), 5000);
		}
		else {
			qDebug() << "�������ʧ��,���������" << endl;
			ui.statusBar->showMessage(tr("�������ʧ��"), 5000);
			QMessageBox::critical(this, "��ʾ", "����˿ڴ�ʧ��");
		}
	}
	else if (ui.buttonCameraConnect->text() == "\346\226\255\345\274\200")
	{
		camera.exit();
		int closeFlag = camera.cameraDisconnect();
		if (closeFlag)
		{
			//�������߳�
			if (camera.isRunning()) {
				camera.stop_flag = true;
				camera.wait();
			}
			//�������ʹ����
			ui.buttonCameraPhoto->setEnabled(false);
			ui.buttonCameraPath->setEnabled(false);
			ui.lineEditCameraPath->setEnabled(false);
			ui.checkBoxShowImage->setEnabled(false);
			ui.checkBoxHighContrast->setEnabled(false);
			ui.buttonCameraConnect->setText(QApplication::translate("LIDARClass", "\350\277\236\346\216\245", nullptr));		//��Ϊ�����ӡ�
			QMessageBox::information(this, "��ʾ", "��������ѶϿ�");
		}
	}
}


void AutoFocus::on_chacekBoxShowImage()
{	//��ʾʵʱͼ��ۺ���
	if (ui.checkBoxShowImage->isChecked()) {
		camera.pause_flag = false;
		//camera.stop_flag = false;
		cv::namedWindow("Live", cv::WINDOW_GUI_NORMAL);  // ��������
	}
	else {
		camera.pause_flag = true;
	}
}

void AutoFocus::cameraPhoto_show(int flag)
{	//�ź���Ӧ-���֡ʵʱ��ʾ
	//ui.labelImage->setPixmap(QPixmap::fromImage(camera.photoQImage));
	cv::Mat imageShow;
	camera.photoCV.convertTo(imageShow, CV_8U, 1.0 / 256);
	imshow("Live", imageShow);
	cv::waitKey(2);	//���̰���������رա�
}

void AutoFocus::on_buttonCameraPhoto_clicked()
{	//���հ�ť�ۺ���
	QDateTime curDateTime = QDateTime::currentDateTime();
	//const char* fileName = "Resources/image/img"+curDateTime.toString("yyyyMMddhhmmss")+".tif";
	cv::String filePath = "Resources/image/img.tif";
	if (camera.isRunning() && ui.checkBoxShowImage->isChecked())
	{
		cv::imwrite(filePath, camera.photoCV);
		//output_data(fileName, (char *)camera.buf, camera.width* 2 * camera.height);
		ui.statusBar->showMessage(tr("��Ƭ�ѱ����� ../Resources/image/img.tif"), 5000);
	}
	else
	{	//��õ�ǰ֡ͼ��
		int flag = camera.accessImages(ui.checkBoxHighContrast->isChecked());
		if (flag)
		{
			qDebug() << "�����ȡͼ��ʧ�ܣ��������" << flag << endl;
			QMessageBox::critical(this, "��ʾ", "�����ȡͼ��ʧ��");
		}
		else
		{
			cv::namedWindow("AutoFocusing", cv::WINDOW_GUI_NORMAL);  // ��������
			cv::Mat img = camera2openCV(camera.buf, camera.width, camera.height, camera.rowbytes);
			cv::imwrite("Resources/image/imgB.tif",img);
			ui.statusBar->showMessage(tr("��Ƭ�ѱ����� ../Resources/image/imgB.tif"), 5000);
			img.convertTo(img, CV_8U, 1.0 / 256);
			imshow("AutoFocusing", img);
			cv::waitKey(0);	//���̰���������رա�
		}
	}
}

void AutoFocus::on_buttonMotorConnect_clicked()
{	//���ӵ����ť�ۺ���
	if (ui.buttonMotorConnect->text() == "\350\277\236\346\216\245")
	{
		//���ô��ں�  
		serialPortName = ui.comMotorCom->currentText();
		int openFlag = motorSerial.openSerial(serialPortName);
		if (openFlag)
		{
			//�������ʹ��
			ui.spinMotorAdress->setEnabled(true);
			ui.spinMotorDirction->setEnabled(true);
			ui.spinMotorSpeed->setEnabled(true);
			ui.spinMotorStep->setEnabled(true);
			ui.buttonMotorSet->setEnabled(true);
			ui.buttonMotorLeft->setEnabled(true);
			ui.buttonMotorRight->setEnabled(true);

			//�ı����Ӱ�ť	
			ui.comMotorCom->setEnabled(false);
			ui.buttonMotorConnect->setText(QApplication::translate("LIDARClass", "\346\226\255\345\274\200", nullptr));		//��Ϊ���Ͽ���
			ui.statusBar->showMessage(tr("���Ƶ���˿�%1���ӳɹ�").arg(serialPortName), 3000);
		}
		else
		{
			qDebug() << QObject::tr("Failed to open port %1, error: %2")
				.arg(serialPortName).arg(serialPort.errorString())
				<< endl;
			ui.statusBar->showMessage(tr("���Ƶ���˿�%1����ʧ��").arg(serialPortName), 5000);
			QMessageBox::critical(this, "��ʾ", "���Ƶ���˿ڴ�ʧ��");
		}
	}
	else if (ui.buttonMotorConnect->text() == "\346\226\255\345\274\200")
	{
		int closeFlag = motorSerial.closeSerial();
		if (closeFlag)
		{
			//�������ʹ����
			ui.spinMotorAdress->setEnabled(false);
			ui.spinMotorDirction->setEnabled(false);
			ui.spinMotorSpeed->setEnabled(false);
			ui.spinMotorStep->setEnabled(false);
			ui.buttonMotorSet->setEnabled(false);
			ui.buttonMotorLeft->setEnabled(false);
			ui.buttonMotorRight->setEnabled(false);
			ui.comMotorCom->setEnabled(true);
			ui.buttonMotorConnect->setText(QApplication::translate("LIDARClass", "\350\277\236\346\216\245", nullptr));		//��Ϊ�����ӡ�
			ui.statusBar->showMessage(tr("���Ƶ���˿��ѹر�").arg(serialPortName), 5000);
			QMessageBox::information(this, "��ʾ", "���Ƶ���˿��ѹر�");
		}
	}
	else {
		ui.buttonMotorConnect->setText(QApplication::translate("LIDARClass", "\350\277\236\346\216\245", nullptr));		//��Ϊ�����ӡ�
		QMessageBox::information(this, "��ʾ", "���Ƶ���˿��ѹر�");
	}
}

void AutoFocus::on_buttonMotorSet_clicked()
{	//������Ʋ������òۺ���
	char timev[100];
	tm* localTime;
	time_t timep = time(NULL);
	localTime = localtime(&timep); //תΪ����ʱ��  
	strftime(timev, 64, "%Y%m%d%H%M%S", localTime);
	std::cout << "time():" << timev << std::endl;
}

void AutoFocus::on_actionFileOpen_triggered()
{	//�˵������򿪡��ۺ���
	QString curPath = QDir::currentPath();	//��ȡӦ�ó���ǰĿ¼
	QString dlgTitle = "���ļ�";
	QString filter = "ͼ���ļ�(*.tif *.jpg *.png *.bmp *.raw);;�����ļ�(*.*)";
	QString aFileName = QFileDialog::getOpenFileName(this, dlgTitle, curPath, filter);
	qDebug() << aFileName << endl;
}

void AutoFocus::closeEvent(QCloseEvent * event)
{	//��д���ڹر��¼�����������߳�
	if (camera.isRunning())
	{
		camera.cameraDisconnect();
		camera.wait();
	}
	event->accept();
}
