#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>
#include <QMainWindow>
#include <QComboBox>
#include <QTextEdit>
#include <QtEndian>
#include <QByteArray>
#include <QAudioFormat>
#include <QAudioBuffer>
#include <QAudioRecorder>
#include <QAudioFormat>
#include <QDir>
#include <QAudioDeviceInfo>
#include <QAudioOutput>
#include <QBuffer>
#include <QSpinBox>

#include "tcpserver.h"
#include "wavfile.h"
#include "sinesweep.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    void writeFile();
    ~MainWindow();
public slots:
    void messageReceived(std::string message);
    void removeIP(QString peerAddress);
    void addAddressList(std::string peerAddress);
    void onControlReceived(int control);
    void selectPath();
    void writeData(QList<QByteArray> &data);
    void defineLen(int len);
    void handleStepperControl();

signals:
    void IpSelected(QString AndroidAddress, QString ArduinoAddress);

private slots:

    void on_startRecord_clicked();


    void on_stopRecord_clicked();

    void on_ButtonSelectSignal_clicked();

    void deviceChanged(int index);

    void on_TestSignalPlay_clicked();

    void handleStateChanged(QAudio::State newState);

    void on_stepPlus_clicked();

    void on_stepMin_clicked();

    void on_StepSpin_valueChanged(int arg1);

    void on_automaticTest_clicked();

    void androidIpChanged(int index);

    void arduinoIpChanged(int index);

private:
    void writeWavFile();
    void readSignalData(QString filepath);
    void initializeAudio(const QAudioDeviceInfo &deviceInfo);
    Ui::MainWindow * ui;

    /* Variables of UI */
    QComboBox * ArduinoIP = nullptr;
    QComboBox * AndroidIP = nullptr;
    QSpinBox * stepCount = nullptr;
    QComboBox * m_deviceBox = nullptr;

    // Variable for IP select
    bool changed = false;


    TcpServer * _server = nullptr;
    quint16 port{4242};

    int nrOfBytes;
    int nrOfSamples;
    WavPcmFile * m_file;
    QFile * file;
    bool recording{false};

    QAudioFormat *format;
    QByteArray * _data = nullptr;
    QAudioBuffer* buffer;
    QAudioRecorder * recorder;

    // Variables for file storing
    QString pathToDir;
    QString pathToFile;
    QDir * dir = nullptr;
    int recordIndex = 0;

    // Variables for signal select
    QFile m_signalTrack;
    QList<QByteArray> m_signalData;

    QAudioOutput * m_audioOutput = nullptr;
    QBuffer m_buffer;

    // Variables for motor control
    int counterSteps = 0;

    // Variables for automated test procedure
    int testCount = 40;
    bool automatic = false;

};

#endif // MAINWINDOW_H
