/********************************************************************************
** Form generated from reading UI file 'AutoFocus.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTOFOCUS_H
#define UI_AUTOFOCUS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AutoFocusClass
{
public:
    QAction *actionFileOpen;
    QAction *actionExit;
    QWidget *centralWidget;
    QGridLayout *gridLayout_4;
    QGroupBox *groupImage;
    QGridLayout *gridLayout;
    QLabel *labelImage;
    QGroupBox *groupMotor;
    QGridLayout *gridLayout_2;
    QSpinBox *spinMotorDirction;
    QSpinBox *spinMotorAdress;
    QLabel *labelMotorDirction;
    QPushButton *buttonMotorRight;
    QSpinBox *spinMotorSpeed;
    QSpinBox *spinMotorStep;
    QLabel *labelMotorSpeed;
    QPushButton *buttonMotorConnect;
    QPushButton *buttonMotorSet;
    QLabel *labelMotorAdress;
    QLabel *labelMotorCom;
    QPushButton *buttonMotorLeft;
    QLabel *labelMotorStep;
    QComboBox *comMotorCom;
    QGroupBox *groupCamera;
    QGridLayout *gridLayout_3;
    QPushButton *buttonCameraPath;
    QPushButton *buttonCameraConnect;
    QLineEdit *lineEditCameraPath;
    QCheckBox *checkBoxShowImage;
    QCheckBox *checkBoxHighContrast;
    QPushButton *buttonCameraPhoto;
    QLabel *labelCameraPath;
    QSpacerItem *verticalSpacer;
    QMenuBar *menuBar;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *AutoFocusClass)
    {
        if (AutoFocusClass->objectName().isEmpty())
            AutoFocusClass->setObjectName(QString::fromUtf8("AutoFocusClass"));
        AutoFocusClass->resize(794, 587);
        actionFileOpen = new QAction(AutoFocusClass);
        actionFileOpen->setObjectName(QString::fromUtf8("actionFileOpen"));
        actionExit = new QAction(AutoFocusClass);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        centralWidget = new QWidget(AutoFocusClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_4 = new QGridLayout(centralWidget);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        groupImage = new QGroupBox(centralWidget);
        groupImage->setObjectName(QString::fromUtf8("groupImage"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupImage->sizePolicy().hasHeightForWidth());
        groupImage->setSizePolicy(sizePolicy);
        groupImage->setMinimumSize(QSize(200, 200));
        groupImage->setMaximumSize(QSize(2048, 2048));
        groupImage->setSizeIncrement(QSize(1, 0));
        gridLayout = new QGridLayout(groupImage);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        labelImage = new QLabel(groupImage);
        labelImage->setObjectName(QString::fromUtf8("labelImage"));
        labelImage->setMinimumSize(QSize(50, 50));
        labelImage->setMaximumSize(QSize(2048, 2048));
        labelImage->setPixmap(QPixmap(QString::fromUtf8("Resources/image/lena.jpg")));
        labelImage->setScaledContents(true);

        gridLayout->addWidget(labelImage, 0, 0, 1, 1);


        gridLayout_4->addWidget(groupImage, 0, 1, 2, 1);

        groupMotor = new QGroupBox(centralWidget);
        groupMotor->setObjectName(QString::fromUtf8("groupMotor"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(3);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupMotor->sizePolicy().hasHeightForWidth());
        groupMotor->setSizePolicy(sizePolicy1);
        gridLayout_2 = new QGridLayout(groupMotor);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        spinMotorDirction = new QSpinBox(groupMotor);
        spinMotorDirction->setObjectName(QString::fromUtf8("spinMotorDirction"));
        spinMotorDirction->setEnabled(false);
        spinMotorDirction->setMaximum(1);

        gridLayout_2->addWidget(spinMotorDirction, 3, 1, 1, 2);

        spinMotorAdress = new QSpinBox(groupMotor);
        spinMotorAdress->setObjectName(QString::fromUtf8("spinMotorAdress"));
        spinMotorAdress->setEnabled(false);
        spinMotorAdress->setMaximum(10);
        spinMotorAdress->setValue(1);

        gridLayout_2->addWidget(spinMotorAdress, 2, 1, 1, 2);

        labelMotorDirction = new QLabel(groupMotor);
        labelMotorDirction->setObjectName(QString::fromUtf8("labelMotorDirction"));
        labelMotorDirction->setEnabled(true);
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(labelMotorDirction->sizePolicy().hasHeightForWidth());
        labelMotorDirction->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(labelMotorDirction, 3, 0, 1, 1);

        buttonMotorRight = new QPushButton(groupMotor);
        buttonMotorRight->setObjectName(QString::fromUtf8("buttonMotorRight"));
        buttonMotorRight->setEnabled(false);
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(1);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(buttonMotorRight->sizePolicy().hasHeightForWidth());
        buttonMotorRight->setSizePolicy(sizePolicy3);

        gridLayout_2->addWidget(buttonMotorRight, 6, 2, 1, 2);

        spinMotorSpeed = new QSpinBox(groupMotor);
        spinMotorSpeed->setObjectName(QString::fromUtf8("spinMotorSpeed"));
        spinMotorSpeed->setEnabled(false);

        gridLayout_2->addWidget(spinMotorSpeed, 4, 1, 1, 2);

        spinMotorStep = new QSpinBox(groupMotor);
        spinMotorStep->setObjectName(QString::fromUtf8("spinMotorStep"));
        spinMotorStep->setEnabled(false);

        gridLayout_2->addWidget(spinMotorStep, 5, 1, 1, 2);

        labelMotorSpeed = new QLabel(groupMotor);
        labelMotorSpeed->setObjectName(QString::fromUtf8("labelMotorSpeed"));
        labelMotorSpeed->setEnabled(true);
        sizePolicy2.setHeightForWidth(labelMotorSpeed->sizePolicy().hasHeightForWidth());
        labelMotorSpeed->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(labelMotorSpeed, 4, 0, 1, 1);

        buttonMotorConnect = new QPushButton(groupMotor);
        buttonMotorConnect->setObjectName(QString::fromUtf8("buttonMotorConnect"));

        gridLayout_2->addWidget(buttonMotorConnect, 0, 3, 1, 1);

        buttonMotorSet = new QPushButton(groupMotor);
        buttonMotorSet->setObjectName(QString::fromUtf8("buttonMotorSet"));
        buttonMotorSet->setEnabled(false);
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(buttonMotorSet->sizePolicy().hasHeightForWidth());
        buttonMotorSet->setSizePolicy(sizePolicy4);

        gridLayout_2->addWidget(buttonMotorSet, 2, 3, 4, 1);

        labelMotorAdress = new QLabel(groupMotor);
        labelMotorAdress->setObjectName(QString::fromUtf8("labelMotorAdress"));
        labelMotorAdress->setEnabled(true);
        sizePolicy2.setHeightForWidth(labelMotorAdress->sizePolicy().hasHeightForWidth());
        labelMotorAdress->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(labelMotorAdress, 2, 0, 1, 1);

        labelMotorCom = new QLabel(groupMotor);
        labelMotorCom->setObjectName(QString::fromUtf8("labelMotorCom"));
        sizePolicy2.setHeightForWidth(labelMotorCom->sizePolicy().hasHeightForWidth());
        labelMotorCom->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(labelMotorCom, 0, 0, 1, 1);

        buttonMotorLeft = new QPushButton(groupMotor);
        buttonMotorLeft->setObjectName(QString::fromUtf8("buttonMotorLeft"));
        buttonMotorLeft->setEnabled(false);
        sizePolicy3.setHeightForWidth(buttonMotorLeft->sizePolicy().hasHeightForWidth());
        buttonMotorLeft->setSizePolicy(sizePolicy3);

        gridLayout_2->addWidget(buttonMotorLeft, 6, 0, 1, 2);

        labelMotorStep = new QLabel(groupMotor);
        labelMotorStep->setObjectName(QString::fromUtf8("labelMotorStep"));
        labelMotorStep->setEnabled(true);
        sizePolicy2.setHeightForWidth(labelMotorStep->sizePolicy().hasHeightForWidth());
        labelMotorStep->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(labelMotorStep, 5, 0, 1, 1);

        comMotorCom = new QComboBox(groupMotor);
        comMotorCom->setObjectName(QString::fromUtf8("comMotorCom"));
        QSizePolicy sizePolicy5(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(comMotorCom->sizePolicy().hasHeightForWidth());
        comMotorCom->setSizePolicy(sizePolicy5);

        gridLayout_2->addWidget(comMotorCom, 0, 1, 1, 2);


        gridLayout_4->addWidget(groupMotor, 1, 0, 1, 1);

        groupCamera = new QGroupBox(centralWidget);
        groupCamera->setObjectName(QString::fromUtf8("groupCamera"));
        sizePolicy1.setHeightForWidth(groupCamera->sizePolicy().hasHeightForWidth());
        groupCamera->setSizePolicy(sizePolicy1);
        gridLayout_3 = new QGridLayout(groupCamera);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        buttonCameraPath = new QPushButton(groupCamera);
        buttonCameraPath->setObjectName(QString::fromUtf8("buttonCameraPath"));
        buttonCameraPath->setEnabled(false);

        gridLayout_3->addWidget(buttonCameraPath, 5, 2, 1, 1);

        buttonCameraConnect = new QPushButton(groupCamera);
        buttonCameraConnect->setObjectName(QString::fromUtf8("buttonCameraConnect"));
        QSizePolicy sizePolicy6(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(buttonCameraConnect->sizePolicy().hasHeightForWidth());
        buttonCameraConnect->setSizePolicy(sizePolicy6);

        gridLayout_3->addWidget(buttonCameraConnect, 0, 0, 1, 3);

        lineEditCameraPath = new QLineEdit(groupCamera);
        lineEditCameraPath->setObjectName(QString::fromUtf8("lineEditCameraPath"));
        lineEditCameraPath->setEnabled(false);
        sizePolicy6.setHeightForWidth(lineEditCameraPath->sizePolicy().hasHeightForWidth());
        lineEditCameraPath->setSizePolicy(sizePolicy6);

        gridLayout_3->addWidget(lineEditCameraPath, 5, 1, 1, 1);

        checkBoxShowImage = new QCheckBox(groupCamera);
        checkBoxShowImage->setObjectName(QString::fromUtf8("checkBoxShowImage"));
        checkBoxShowImage->setEnabled(false);

        gridLayout_3->addWidget(checkBoxShowImage, 1, 0, 1, 3);

        checkBoxHighContrast = new QCheckBox(groupCamera);
        checkBoxHighContrast->setObjectName(QString::fromUtf8("checkBoxHighContrast"));
        checkBoxHighContrast->setEnabled(false);
        checkBoxHighContrast->setChecked(true);

        gridLayout_3->addWidget(checkBoxHighContrast, 3, 0, 1, 1);

        buttonCameraPhoto = new QPushButton(groupCamera);
        buttonCameraPhoto->setObjectName(QString::fromUtf8("buttonCameraPhoto"));
        buttonCameraPhoto->setEnabled(false);
        sizePolicy6.setHeightForWidth(buttonCameraPhoto->sizePolicy().hasHeightForWidth());
        buttonCameraPhoto->setSizePolicy(sizePolicy6);
        buttonCameraPhoto->setMinimumSize(QSize(0, 30));

        gridLayout_3->addWidget(buttonCameraPhoto, 4, 0, 1, 3);

        labelCameraPath = new QLabel(groupCamera);
        labelCameraPath->setObjectName(QString::fromUtf8("labelCameraPath"));

        gridLayout_3->addWidget(labelCameraPath, 5, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 2, 0, 1, 1);


        gridLayout_4->addWidget(groupCamera, 0, 0, 1, 1);

        AutoFocusClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(AutoFocusClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 794, 23));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        AutoFocusClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(AutoFocusClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        AutoFocusClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(AutoFocusClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        AutoFocusClass->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menu->addAction(actionFileOpen);
        menu->addSeparator();
        menu->addAction(actionExit);

        retranslateUi(AutoFocusClass);
        QObject::connect(actionExit, SIGNAL(triggered()), AutoFocusClass, SLOT(close()));

        QMetaObject::connectSlotsByName(AutoFocusClass);
    } // setupUi

    void retranslateUi(QMainWindow *AutoFocusClass)
    {
        AutoFocusClass->setWindowTitle(QApplication::translate("AutoFocusClass", "AutoFocus", nullptr));
        actionFileOpen->setText(QApplication::translate("AutoFocusClass", "\346\211\223\345\274\200", nullptr));
#ifndef QT_NO_TOOLTIP
        actionFileOpen->setToolTip(QApplication::translate("AutoFocusClass", "\346\211\223\345\274\200\345\233\276\345\203\217\346\226\207\344\273\266", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionFileOpen->setShortcut(QApplication::translate("AutoFocusClass", "Ctrl+O", nullptr));
#endif // QT_NO_SHORTCUT
        actionExit->setText(QApplication::translate("AutoFocusClass", "\351\200\200\345\207\272", nullptr));
        groupImage->setTitle(QApplication::translate("AutoFocusClass", "\345\256\236\346\227\266\345\233\276\345\203\217", nullptr));
        labelImage->setText(QString());
        groupMotor->setTitle(QApplication::translate("AutoFocusClass", "\347\224\265\346\234\272", nullptr));
        labelMotorDirction->setText(QApplication::translate("AutoFocusClass", "\346\226\271\345\220\221", nullptr));
        buttonMotorRight->setText(QApplication::translate("AutoFocusClass", "\342\206\222", nullptr));
        labelMotorSpeed->setText(QApplication::translate("AutoFocusClass", "\351\200\237\345\272\246", nullptr));
        buttonMotorConnect->setText(QApplication::translate("AutoFocusClass", "\350\277\236\346\216\245", nullptr));
        buttonMotorSet->setText(QApplication::translate("AutoFocusClass", "\350\256\276\347\275\256", nullptr));
        labelMotorAdress->setText(QApplication::translate("AutoFocusClass", "\345\234\260\345\235\200", nullptr));
        labelMotorCom->setText(QApplication::translate("AutoFocusClass", "\347\253\257\345\217\243\345\217\267", nullptr));
        buttonMotorLeft->setText(QApplication::translate("AutoFocusClass", "\342\206\220", nullptr));
        labelMotorStep->setText(QApplication::translate("AutoFocusClass", "\350\241\214\347\250\213", nullptr));
        groupCamera->setTitle(QApplication::translate("AutoFocusClass", "\347\233\270\346\234\272", nullptr));
        buttonCameraPath->setText(QApplication::translate("AutoFocusClass", "\346\265\217\350\247\210", nullptr));
        buttonCameraConnect->setText(QApplication::translate("AutoFocusClass", "\350\277\236\346\216\245", nullptr));
        checkBoxShowImage->setText(QApplication::translate("AutoFocusClass", "\346\230\276\347\244\272\345\256\236\346\227\266\345\233\276\345\203\217", nullptr));
        checkBoxHighContrast->setText(QApplication::translate("AutoFocusClass", "\351\253\230\345\257\271\346\257\224\345\272\246\346\250\241\345\274\217", nullptr));
        buttonCameraPhoto->setText(QApplication::translate("AutoFocusClass", "\346\213\215\347\205\247", nullptr));
        labelCameraPath->setText(QApplication::translate("AutoFocusClass", "\350\267\257\345\276\204", nullptr));
        menu->setTitle(QApplication::translate("AutoFocusClass", "\346\226\207\344\273\266", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AutoFocusClass: public Ui_AutoFocusClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTOFOCUS_H
