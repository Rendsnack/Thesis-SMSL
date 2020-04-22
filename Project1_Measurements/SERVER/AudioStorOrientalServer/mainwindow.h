#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "wavfile.h"

#include <QMainWindow>
#include <QTextEdit>
#include <tcpserver.h>
#include <memory>
#include <QtEndian>
#include <QByteArray>
#include <QAudioFormat>
#include <QAudioBuffer>
#include <QAudioRecorder>
#include "sinesweep.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void writeWavFile();
    void writeFile();
    ~MainWindow();
public slots:
    void onNewConnection();
    void onSocketStateChanged(QAbstractSocket::SocketState socketState);
    void onReadyRead();
    void onRecordStart();


    //SLOT now connected to signal::clicked from pushbutton TASK: connect to signal emitted by sinesweep generator
    void onRecordStop();
private:
    Ui::MainWindow *ui;
    QTcpServer * _server = nullptr;
    QTcpSocket * _socket = nullptr;
    QHostAddress address;
    quint16 port{4242};
    bool fileNameReceived{false};
    bool dataIncoming{false};
    int nrOfBytes;
    int nrOfSamples;
    WavPcmFile * m_file;
    QFile * file;
    bool recording{false};

    QAudioFormat *format;
    QByteArray *data;
    QAudioBuffer* buffer;
    QAudioRecorder * recorder;
    SineSweep * sweep;



    // Variables for file storing
    QString pathToDir = "D:/Master/Thesis/Development/Data";
    QString pathToFile;
    QDir dir;

    // Variables for sinesweep




};
#endif // MAINWINDOW_H
