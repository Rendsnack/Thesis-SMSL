#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    stepCount = ui->StepSpin;
    stepCount->setRange(1,10);
    m_deviceBox = new QComboBox(ui->deviceBox);
    const QAudioDeviceInfo &defaultDeviceInfo = QAudioDeviceInfo::defaultOutputDevice();
    m_deviceBox->addItem(defaultDeviceInfo.deviceName(), qVariantFromValue(defaultDeviceInfo));
    for (auto &deviceInfo: QAudioDeviceInfo::availableDevices(QAudio::AudioOutput)) {
        if (deviceInfo != defaultDeviceInfo)
            m_deviceBox->addItem(deviceInfo.deviceName(), qVariantFromValue(deviceInfo));
    }
    initializeAudio(QAudioDeviceInfo::defaultOutputDevice());
    connect(m_deviceBox, QOverload<int>::of(&QComboBox::activated), this, &MainWindow::deviceChanged);
    ArduinoIP = ui->ArduinoIPSel;
    connect(ArduinoIP, QOverload<int>::of(&QComboBox::activated), this, &MainWindow::arduinoIpChanged);
    ArduinoIP->addItem("None");

    AndroidIP = ui->AndroidIPSel;
    AndroidIP->addItem("None");
    connect(ArduinoIP, QOverload<int>::of(&QComboBox::activated), this, &MainWindow::androidIpChanged);
    _server = new TcpServer();
    _server->listen(QHostAddress::Any, port);
    ui->log->append("Server is listening on address: " + _server->serverAddress().toString() + " on port: " + QString::number(_server->serverPort()) + "\n");
    connect(_server, SIGNAL(newConnection()), _server, SLOT(onNewConnection()));
    connect(_server, SIGNAL(connectionReceived(std::string)), this, SLOT(addAddressList(std::string)));
    connect(_server, SIGNAL(dataReceived(QList<QByteArray> &)), this, SLOT(writeData(QList<QByteArray> &)));
    connect(_server, SIGNAL(messageReceived(std::string)), this, SLOT(messageReceived(std::string)));
    connect(this, SIGNAL(IpSelected(QString, QString)), _server, SLOT(updateSocketDeviceType(QString, QString)));
    connect(_server, SIGNAL(removeIP(QString)), this, SLOT(removeIP(QString)));
    connect(_server, SIGNAL(controlReceived(int)), this, SLOT(onControlReceived(int)));
    connect(_server, SIGNAL(dataTransmitEnd()), this, SLOT(selectPath()));
    connect(_server, SIGNAL(stepperRotated()),this, SLOT(handleStepperControl()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::messageReceived(std::string message)
{
    ui->log->append(message.c_str());

}

void MainWindow::removeIP(QString peerAddress)
{
    int index = ArduinoIP->findText(peerAddress);
    ArduinoIP->removeItem(index);
    index = AndroidIP->findText(peerAddress);
    AndroidIP->removeItem(index);

}

void MainWindow::addAddressList(std::string peerAddress)
{
    ArduinoIP->addItem(QString(peerAddress.c_str()));
    AndroidIP->addItem(QString(peerAddress.c_str()));
}

void MainWindow::onControlReceived(int control)
{
    switch(control){
    case 1: //START RECORD successfull
        recording = true;
        ui->log->append("Started recording... \n");
        if(automatic){
            //2: start playing signal
            initializeAudio(m_deviceBox->currentData().value<QAudioDeviceInfo>());
            m_signalTrack.open(QIODevice::ReadOnly);
            m_audioOutput->start(&m_signalTrack);
        }
        break;
    case 2: //STOP RECORD successfull
        recording = false;
        ui->log->append("Stopped recording. \n");
        std::string androidPeer = AndroidIP->currentText().toStdString();
        _server->sendMessage(androidPeer, "3 \n");

        break;
    }
}

void MainWindow::selectPath(){
    if(dir == nullptr){
        QFileDialog dialog(this);
        dialog.setFileMode(QFileDialog::DirectoryOnly);
        dir = new QDir(QFileDialog::getExistingDirectory(0, ("Select Output Folder"), QDir::currentPath()));

        if(!dialog.exec()){ // user pressed cancel button
            ui->log->append("No directory selected \n");
        }
        else
        {
            ui->log->append("Directory selected: " + dir->absolutePath() + "\n");
            writeWavFile();
        }
    }
    else
        writeWavFile();

}

void MainWindow::writeWavFile(){
    format = new QAudioFormat();
    format->setSampleRate(44100);
    format->setChannelCount(1);
    format->setSampleSize(16);
    format->setCodec("audio/pcm");
    format->setByteOrder(QAudioFormat::LittleEndian);
    format->setSampleType(QAudioFormat::SignedInt);

    // Change this with the movement of the stepper
    pathToFile = dir->absolutePath() + "/record" + QString::number(recordIndex) + ".wav";
    recordIndex++;
    m_file = new WavPcmFile(pathToFile, *format);

    if(m_file->open()){
        m_file->write(*_data);
        m_file->close();
        ui->log->append("File written at: " + pathToFile);
        if(automatic){
            //5: Rotate stepper
            counterSteps++;
            std::string peerAddress = ArduinoIP->currentText().toStdString();
            _server->sendControl(peerAddress,'5');
            ui->counterText->setText(QString::number(counterSteps));
        }

    }
    else
        ui->log->append("file could not be written");
}

void MainWindow::readSignalData(QString filepath)
{
    QFile file(filepath);
    if(!file.open(QIODevice::ReadOnly)){
        ui->log->append("Error opening signal file: " + file.errorString() + "\n");
    }
    QByteArray rawData = file.readAll();
    m_signalData = rawData.split(',');

    file.close();


}

void MainWindow::initializeAudio(const QAudioDeviceInfo &deviceInfo)
{
    QAudioFormat format;
    format.setSampleRate(44100);
    format.setChannelCount(1);
    format.setSampleSize(16);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);
    if (!deviceInfo.isFormatSupported(format)) {
        qWarning() << "Default format not supported - trying to use nearest";
        format = deviceInfo.nearestFormat(format);
    }
    m_audioOutput = new QAudioOutput(deviceInfo, format);

    connect(m_audioOutput, &QAudioOutput::stateChanged, this, &MainWindow::handleStateChanged);
}

void MainWindow::writeData(QList<QByteArray> &data)
{
    if(_data == nullptr) _data = new QByteArray();
    for (int i = 0; i < data.length(); i++) {
        QByteArray sample = data[i];
        _data->push_back(sample[0]);
    }

}

void MainWindow::defineLen(int len)
{
}

void MainWindow::handleStepperControl()
{
    ui->log->append("Arduino: stepper rotated. \n");
    if(automatic){
        // Redo entire procedure
        testCount--;
        if(testCount == 0){
            automatic = false;
            ui->log->append("Test procedure finished. \n");
        }
        else{
            // Restart
            _data->clear();
            std::string androidPeer = AndroidIP->currentText().toStdString();
            _server->sendMessage(androidPeer, "1 \n");
        }
    }

}

void MainWindow::on_startRecord_clicked()
{
    if(!recording){
        // Send start command to TCPSocket of android
        if(_data != nullptr)
            _data->clear();
        std::string androidPeer = AndroidIP->currentText().toStdString();
        _server->sendMessage(androidPeer, "1 \n");
    }
    else
        ui->log->append("Already recording \n");
}

void MainWindow::on_stopRecord_clicked()
{
    if(recording){
        std::string androidPeer = AndroidIP->currentText().toStdString();
        _server->sendMessage(androidPeer, "2 \n");
    }
    else
        ui->log->append("Not recording yet \n");
}

void MainWindow::on_ButtonSelectSignal_clicked()
{
    QFileDialog dialog(this);
    QString filepath = QFileDialog::getOpenFileName(this,tr("Open Document"),
                                                    QDir::currentPath(),
                                                    tr("wav files (*.wav)"));
    QFileInfo fi(filepath);
    QString filename = fi.baseName() ;

    if(filepath != ""){
        ui->log->append("signal selected: " + filename + "\n");
        ui->signalEdit->setText(filename);
        m_signalTrack.setFileName(filepath);
    }
    else
        ui->log->append("No signal selected!\n");

}

void MainWindow::deviceChanged(int index)
{
    m_audioOutput->stop();
    m_audioOutput->disconnect(this);
    initializeAudio(m_deviceBox->itemData(index).value<QAudioDeviceInfo>());
}

void MainWindow::on_TestSignalPlay_clicked()
{
    // If m_audioOutput has been played before, it will be deleted, so reinitialize it
    initializeAudio(m_deviceBox->currentData().value<QAudioDeviceInfo>());
    m_signalTrack.open(QIODevice::ReadOnly);
    m_audioOutput->start(&m_signalTrack);

}

void MainWindow::handleStateChanged(QAudio::State newState)
{
    switch (newState) {
    case QAudio::IdleState:
        // Finished playing (no more data)
        m_audioOutput->stop();
        m_signalTrack.close();
        delete m_audioOutput;
        m_audioOutput = nullptr;
        if(automatic){
            //3: send stop record message to android
            _server->sendMessage(AndroidIP->currentText().toStdString(), "2 \n");
        }
        break;


    case QAudio::StoppedState:
        // Stopped for other reasons
        if (m_audioOutput->error() != QAudio::NoError) {

        }
        break;

    default:
        // ... other cases as appropriate
        break;
    }

}

void MainWindow::on_stepPlus_clicked()
{
    counterSteps++;
    std::string peerAddress = ArduinoIP->currentText().toStdString();
    _server->sendControl(peerAddress,'5');
    ui->counterText->setText(QString::number(counterSteps));
}

void MainWindow::on_stepMin_clicked()
{
    counterSteps--;
    _server->sendControl(ArduinoIP->currentText().toStdString(), '6');
    ui->counterText->setText(QString::number(counterSteps));
}

void MainWindow::on_StepSpin_valueChanged(int stepSize)
{
    std::string peerAddress = ArduinoIP->currentText().toStdString();
    _server->sendControl(peerAddress, '1');
    _server->sendControl(peerAddress, 48 + stepSize);
}

void MainWindow::on_automaticTest_clicked()
{
    if(dir == nullptr){
        QFileDialog dialog(this);
        dialog.setFileMode(QFileDialog::DirectoryOnly);
        dir = new QDir(QFileDialog::getExistingDirectory(0, ("Select Output Folder"), QDir::currentPath()));

        if(!dialog.exec()){ // user pressed cancel button
            ui->log->append("No directory selected \n");
        }
        else
        {
            ui->log->append("Directory selected: " + dir->absolutePath() + "\n");
        }
    }
    // first check if everything is set
    std::string arduinoAddress = ArduinoIP->currentText().toStdString();
    std::string androidAddress = AndroidIP->currentText().toStdString();
    if(arduinoAddress == "None" || androidAddress == "None"){
        ui->log->append("No Ip addresses selected \n");
    }
    else if(!m_signalTrack.exists())
    {
        ui->log->append("Signal select not correct \n");
    }
    else{
        ui->log->append("Starting automated test procedure.... \n");
        automatic = true;
        testCount = 40;
        ui->counterText->setText("0");
        //1: send first command to initiate procedure
        _server->sendMessage(androidAddress, "1 \n");

    }

}

void MainWindow::androidIpChanged(int index)
{
    if(!changed) //first select
    {
        if(index == 1)
            ArduinoIP->setCurrentIndex(2);
        else if(index == 2)
            ArduinoIP->setCurrentIndex(1);
        changed = true;
    }
    else //second select
        changed = false;
    emit IpSelected(AndroidIP->currentText(), ArduinoIP->currentText());

}

void MainWindow::arduinoIpChanged(int index)
{
    if(!changed) // fi
    {
        if(index == 1)
            AndroidIP->setCurrentIndex(2);
        else if(index == 2)
            AndroidIP->setCurrentIndex(1);
        changed = true;
    }
    else // second select
        changed = false;
    emit IpSelected(AndroidIP->currentText(), ArduinoIP->currentText());
}
