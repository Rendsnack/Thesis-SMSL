#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QAudioFormat>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _server = new QTcpServer();
    _server->listen(QHostAddress::Any, port);
    ui->log->append("Server is listening on address: " + _server->serverAddress().toString() + " on port: " + QString::number(_server->serverPort()) + "\n");
    connect(_server, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
    connect(ui->startRecord, SIGNAL(clicked()), this, SLOT(onRecordStart()));
    connect(ui->stopRecord, SIGNAL(clicked()), this, SLOT(onRecordStop()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onNewConnection()
{
    _socket = _server->nextPendingConnection();
    connect(_socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(_socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(onSocketStateChanged(QAbstractSocket::SocketState)));

    ui->log->append("Device connected! \n");
    ui->log->append("Address: " + _socket->peerAddress().toString() + "\n");
}

void MainWindow::onSocketStateChanged(QAbstractSocket::SocketState socketState)
{
    if (socketState == QAbstractSocket::UnconnectedState)
    {
        QTcpSocket* sender = static_cast<QTcpSocket*>(QObject::sender());
        _socket->close();
        ui->log->append("Device disconnected. \n");

    }
}

void MainWindow::onReadyRead()
{
    QTcpSocket* sender = static_cast<QTcpSocket*>(QObject::sender());
    QByteArray datas = sender->readAll();
    _socket->write(QByteArray::fromStdString(sender->peerAddress().toString().toStdString() + ": " + datas.toStdString()));

    QList<QByteArray> list = datas.split('\n');
    for(int i = 0; i < list.count(); i++){
        QByteArray b = list[i];
        if(b.contains("FILENAME")){
            QList<QByteArray> filenamelist = b.split(',');
            pathToFile = pathToDir+QString(filenamelist[1].toStdString().c_str());
            ui->log->append(pathToFile);
        }
        if(b.contains("started Recording...")){
            ui->log->append(b);
           // sweep = new SineSweep();
        }
        if(dataIncoming){
            if(nrOfBytes > 0){
                data->append(b);
                nrOfBytes--;
                nrOfSamples++;
            }
            else{
                dataIncoming = false;
               // writeFile();
                writeWavFile();
            }

        }
        if(b.contains("DATA START")){
            ui->log->append(b);
            nrOfBytes = list[i+1].toInt();
            data = new QByteArray();
            dataIncoming = true;
            nrOfSamples = 0;
        }
    }
}

void MainWindow::writeFile(){
    QString filepath = pathToFile.split('.').first() + ".txt";
    file = new QFile(filepath);
    if(file->open(QFile::WriteOnly | QIODevice::Append)){
        file->write(reinterpret_cast<const char *>(&data[0]),sizeof(float));
//        QDataStream out(file);
//        //out.writeRawData(reinterpret_cast<const char *>(&data[0]), data.size()*sizeof(float));
//        for (int i = 0;i < data.size(); i++) {
//            float sample = data[i];
//            out.writeRawData(reinterpret_cast<const char *>(&sample), sizeof(float));
//            out << sample;
//        }
        file->close();
    }

    else
        qWarning();
}
void MainWindow::writeWavFile(){
    format = new QAudioFormat();
    format->setSampleRate(44100);
    format->setChannelCount(1);
    format->setSampleSize(16);
    format->setCodec("audio/pcm");
    format->setByteOrder(QAudioFormat::LittleEndian);
    format->setSampleType(QAudioFormat::UnSignedInt);
    m_file = new WavPcmFile(pathToFile, *format);

    if(m_file->open()){
        m_file->write(*data);
        m_file->close();
        ui->log->append("File written at: " + pathToFile);

    }
    else
        ui->log->append("file could not be written");
}
void MainWindow::onRecordStart(){
    if(_socket != nullptr){
        if(_socket->state() == QAbstractSocket::UnconnectedState){
            ui->log->append("No connected socket. \n");
        }
        else{
            // Write command RECORD (hold timer of record start Sinesweep
            QByteArray output;
            QString command = "START RECORD\n";
            output.append(command);
            qint64 ret = _socket->write(output);
            if(ret < 0){
                ui->log->append("Error: " + _socket->errorString());
            }
            recording = true;

        }
    }
}

void MainWindow::onRecordStop()
{
    if(recording){
        if(_socket != nullptr){
            if(_socket->state() == QAbstractSocket::UnconnectedState){
                ui->log->append("No connected socket. \n");
            }
            else{
                // Write command STOPRECORD
                QByteArray output;
                QString command = "STOP RECORD\n";
                output.append(command);
                qint64 ret = _socket->write(output);
                if(ret < 0){
                    ui->log->append("Error: " + _socket->errorString());
                }
                recording = false;

            }
        }
    }


}



