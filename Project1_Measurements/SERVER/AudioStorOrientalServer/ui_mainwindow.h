/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTextEdit *log;
    QLineEdit *lineEdit;
    QPushButton *startRecord;
    QPushButton *stopRecord;
    QLineEdit *ArduinoText;
    QLineEdit *androidText;
    QComboBox *ArduinoIPSel;
    QComboBox *AndroidIPSel;
    QSpinBox *StepSpin;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QLineEdit *counterText;
    QLineEdit *lineEdit_5;
    QPushButton *ButtonSelectSignal;
    QLineEdit *lineEdit_6;
    QLineEdit *signalEdit;
    QComboBox *deviceBox;
    QLineEdit *lineEdit_7;
    QPushButton *TestSignalPlay;
    QPushButton *stepPlus;
    QPushButton *stepMin;
    QPushButton *automaticTest;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        log = new QTextEdit(centralwidget);
        log->setObjectName(QString::fromUtf8("log"));
        log->setGeometry(QRect(20, 230, 241, 281));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(20, 170, 241, 41));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        font.setStyleStrategy(QFont::PreferAntialias);
        lineEdit->setFont(font);
        lineEdit->setAutoFillBackground(false);
        lineEdit->setAlignment(Qt::AlignCenter);
        lineEdit->setReadOnly(true);
        startRecord = new QPushButton(centralwidget);
        startRecord->setObjectName(QString::fromUtf8("startRecord"));
        startRecord->setGeometry(QRect(620, 20, 141, 41));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(startRecord->sizePolicy().hasHeightForWidth());
        startRecord->setSizePolicy(sizePolicy1);
        startRecord->setAutoRepeatInterval(99);
        stopRecord = new QPushButton(centralwidget);
        stopRecord->setObjectName(QString::fromUtf8("stopRecord"));
        stopRecord->setGeometry(QRect(620, 70, 141, 41));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(stopRecord->sizePolicy().hasHeightForWidth());
        stopRecord->setSizePolicy(sizePolicy2);
        ArduinoText = new QLineEdit(centralwidget);
        ArduinoText->setObjectName(QString::fromUtf8("ArduinoText"));
        ArduinoText->setGeometry(QRect(30, 30, 181, 31));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(ArduinoText->sizePolicy().hasHeightForWidth());
        ArduinoText->setSizePolicy(sizePolicy3);
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setWeight(50);
        font1.setStyleStrategy(QFont::PreferAntialias);
        ArduinoText->setFont(font1);
        ArduinoText->setFocusPolicy(Qt::WheelFocus);
        ArduinoText->setToolTipDuration(0);
        ArduinoText->setAutoFillBackground(false);
        ArduinoText->setAlignment(Qt::AlignCenter);
        ArduinoText->setReadOnly(true);
        androidText = new QLineEdit(centralwidget);
        androidText->setObjectName(QString::fromUtf8("androidText"));
        androidText->setGeometry(QRect(30, 80, 181, 31));
        sizePolicy.setHeightForWidth(androidText->sizePolicy().hasHeightForWidth());
        androidText->setSizePolicy(sizePolicy);
        QFont font2;
        font2.setPointSize(10);
        font2.setBold(false);
        font2.setWeight(50);
        font2.setStyleStrategy(QFont::PreferAntialias);
        androidText->setFont(font2);
        androidText->setCursor(QCursor(Qt::IBeamCursor));
        androidText->setAutoFillBackground(false);
        androidText->setAlignment(Qt::AlignCenter);
        androidText->setReadOnly(true);
        ArduinoIPSel = new QComboBox(centralwidget);
        ArduinoIPSel->setObjectName(QString::fromUtf8("ArduinoIPSel"));
        ArduinoIPSel->setGeometry(QRect(252, 40, 221, 21));
        AndroidIPSel = new QComboBox(centralwidget);
        AndroidIPSel->setObjectName(QString::fromUtf8("AndroidIPSel"));
        AndroidIPSel->setGeometry(QRect(252, 80, 221, 21));
        StepSpin = new QSpinBox(centralwidget);
        StepSpin->setObjectName(QString::fromUtf8("StepSpin"));
        StepSpin->setGeometry(QRect(690, 230, 101, 21));
        StepSpin->setMinimum(1);
        StepSpin->setMaximum(40);
        lineEdit_2 = new QLineEdit(centralwidget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(560, 170, 231, 41));
        sizePolicy.setHeightForWidth(lineEdit_2->sizePolicy().hasHeightForWidth());
        lineEdit_2->setSizePolicy(sizePolicy);
        lineEdit_2->setFont(font);
        lineEdit_2->setAutoFillBackground(false);
        lineEdit_2->setAlignment(Qt::AlignCenter);
        lineEdit_2->setReadOnly(true);
        lineEdit_3 = new QLineEdit(centralwidget);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(290, 170, 191, 41));
        sizePolicy.setHeightForWidth(lineEdit_3->sizePolicy().hasHeightForWidth());
        lineEdit_3->setSizePolicy(sizePolicy);
        lineEdit_3->setFont(font);
        lineEdit_3->setAutoFillBackground(false);
        lineEdit_3->setAlignment(Qt::AlignCenter);
        lineEdit_3->setReadOnly(true);
        lineEdit_4 = new QLineEdit(centralwidget);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(560, 260, 121, 21));
        QFont font3;
        font3.setPointSize(9);
        font3.setBold(true);
        font3.setWeight(75);
        lineEdit_4->setFont(font3);
        lineEdit_4->setReadOnly(true);
        counterText = new QLineEdit(centralwidget);
        counterText->setObjectName(QString::fromUtf8("counterText"));
        counterText->setGeometry(QRect(692, 260, 91, 21));
        lineEdit_5 = new QLineEdit(centralwidget);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));
        lineEdit_5->setGeometry(QRect(560, 230, 121, 21));
        lineEdit_5->setFont(font3);
        lineEdit_5->setReadOnly(true);
        ButtonSelectSignal = new QPushButton(centralwidget);
        ButtonSelectSignal->setObjectName(QString::fromUtf8("ButtonSelectSignal"));
        ButtonSelectSignal->setGeometry(QRect(330, 310, 121, 41));
        lineEdit_6 = new QLineEdit(centralwidget);
        lineEdit_6->setObjectName(QString::fromUtf8("lineEdit_6"));
        lineEdit_6->setGeometry(QRect(292, 360, 191, 21));
        lineEdit_6->setFont(font3);
        lineEdit_6->setReadOnly(true);
        signalEdit = new QLineEdit(centralwidget);
        signalEdit->setObjectName(QString::fromUtf8("signalEdit"));
        signalEdit->setGeometry(QRect(290, 390, 191, 21));
        deviceBox = new QComboBox(centralwidget);
        deviceBox->setObjectName(QString::fromUtf8("deviceBox"));
        deviceBox->setGeometry(QRect(290, 260, 191, 21));
        lineEdit_7 = new QLineEdit(centralwidget);
        lineEdit_7->setObjectName(QString::fromUtf8("lineEdit_7"));
        lineEdit_7->setGeometry(QRect(350, 220, 101, 31));
        QFont font4;
        font4.setBold(true);
        font4.setWeight(75);
        lineEdit_7->setFont(font4);
        lineEdit_7->setReadOnly(true);
        TestSignalPlay = new QPushButton(centralwidget);
        TestSignalPlay->setObjectName(QString::fromUtf8("TestSignalPlay"));
        TestSignalPlay->setGeometry(QRect(350, 430, 93, 28));
        stepPlus = new QPushButton(centralwidget);
        stepPlus->setObjectName(QString::fromUtf8("stepPlus"));
        stepPlus->setGeometry(QRect(700, 290, 61, 31));
        QFont font5;
        font5.setPointSize(15);
        font5.setBold(true);
        font5.setWeight(75);
        stepPlus->setFont(font5);
        stepMin = new QPushButton(centralwidget);
        stepMin->setObjectName(QString::fromUtf8("stepMin"));
        stepMin->setGeometry(QRect(610, 290, 61, 31));
        stepMin->setFont(font5);
        automaticTest = new QPushButton(centralwidget);
        automaticTest->setObjectName(QString::fromUtf8("automaticTest"));
        automaticTest->setGeometry(QRect(560, 410, 211, 41));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        lineEdit->setText(QCoreApplication::translate("MainWindow", "LOG WINDOW", nullptr));
        startRecord->setText(QCoreApplication::translate("MainWindow", "START RECORD", nullptr));
        stopRecord->setText(QCoreApplication::translate("MainWindow", "STOP RECORD", nullptr));
        ArduinoText->setText(QCoreApplication::translate("MainWindow", "Arduino IP address", nullptr));
        androidText->setText(QCoreApplication::translate("MainWindow", "Android IP address", nullptr));
        lineEdit_2->setText(QCoreApplication::translate("MainWindow", "STEPPER MOTOR", nullptr));
        lineEdit_3->setText(QCoreApplication::translate("MainWindow", "SIGNAL SELECT", nullptr));
        lineEdit_4->setText(QCoreApplication::translate("MainWindow", "STEP COUNT:  ", nullptr));
        lineEdit_5->setText(QCoreApplication::translate("MainWindow", "STEP SIZE: ", nullptr));
        ButtonSelectSignal->setText(QCoreApplication::translate("MainWindow", "SELECT SIGNAL", nullptr));
        lineEdit_6->setText(QCoreApplication::translate("MainWindow", "Selected Signal:", nullptr));
        lineEdit_7->setText(QCoreApplication::translate("MainWindow", "CHANNEL: ", nullptr));
        TestSignalPlay->setText(QCoreApplication::translate("MainWindow", "Test audio", nullptr));
        stepPlus->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        stepMin->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        automaticTest->setText(QCoreApplication::translate("MainWindow", "Run automatic", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
