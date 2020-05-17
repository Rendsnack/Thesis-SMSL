#include "tcpserver.h"

TcpServer::TcpServer()
{

}

void TcpServer::sendMessage(std::string peerAddress, std::string message)
{
    QTcpSocket * _socket = *std::find_if(_sockets.begin(), _sockets.end(),
                                         [&peerAddress](QTcpSocket * obj){
            return obj->peerAddress().toString().toStdString() ==peerAddress;
});

    qDebug() << _socket;
    if(_socket != nullptr){
        if(_socket->state() == QAbstractSocket::UnconnectedState){
            emit connectionReceived("No socket connected");
        }
        else{
            // Write command RECORD (hold timer of record start Sinesweep
            QByteArray output;
            output.append(message.c_str());
            qint64 ret = _socket->write(output);
            if(ret < 0){
                emit messageReceived("Error: " + _socket->errorString().toStdString());
            }
        }
    }

}

void TcpServer::sendControl(std::string peerAddress, char key)
{
    QTcpSocket * _socket = *std::find_if(_sockets.begin(), _sockets.end(),
                                         [&peerAddress](QTcpSocket * obj){
            return obj->peerAddress().toString().toStdString() ==peerAddress;
});

    qDebug() << _socket;
    if(_socket != nullptr){
        if(_socket->state() == QAbstractSocket::UnconnectedState){
            emit connectionReceived("No socket connected");
        }
        else{
            QByteArray output;
            output.append(key);
            qint64 ret = _socket->write(output);
            if(ret < 0){
                emit messageReceived("Error: " + _socket->errorString().toStdString());
            }
        }
    }

}

// Need to override QTcpServer::incomingConnection and use SocketDescriptor
void TcpServer::onNewConnection()
{

    QTcpSocket * i = this->nextPendingConnection();
    _sockets.push_back(i);
    
    connect(i, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(i, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(onSocketStateChanged(QAbstractSocket::SocketState)));
    std::string peerAddress = i->peerAddress().toString().toStdString();
    emit connectionReceived(peerAddress);
    int peerPort = i->peerPort();
    emit messageReceived("Server: Device connected \n Ip Address: \n " + peerAddress + "\n Port: " + std::to_string(peerPort));
    
}

void TcpServer::onSocketStateChanged(QAbstractSocket::SocketState socketState)
{
    if (socketState == QAbstractSocket::UnconnectedState)
    {
        auto i =std::find(_sockets.begin(), _sockets.end(), QObject::sender());
        emit messageReceived("Server:socket closed\n IP: " + (*i)->peerAddress().toString().toStdString());
        emit removeIP((*i)->peerAddress().toString());
        (*i)->close();
    }

}

void TcpServer::onSendControl(std::string controlMessage)
{

}

void TcpServer::onReadyRead()
{

    QTcpSocket* sender = static_cast<QTcpSocket*>(QObject::sender());
    QByteArray datas = sender->readAll();
    QList<QByteArray> list = datas.split('\n');
    if(sender->peerAddress().toString() == androidAddress)
        handleAndroidData(list);
    else if (sender->peerAddress().toString() == arduinoAddress)
        handleArduinoData(list);
}

void TcpServer::updateSocketDeviceType(QString androidAddress, QString arduinoAddress)
{

    this->androidAddress = androidAddress;
    this->arduinoAddress = arduinoAddress;

}

void TcpServer::handleAndroidData(QList<QByteArray> list)
{
    if(_dataLen == 0){
        switch(int key = list[0].toInt()){
        case 1:  // Log message:
            emit messageReceived("Android: " + list[1].toStdString());
            break;

        case 2: // Control message: started recording
            emit controlReceived(list[1].toInt());
            break;
        case 3: // data incoming:
            _dataLen = list[1].toLong();
            emit lengthReceived(_dataLen);
            if(list[2] != "" && list.length() == 3){
                QByteArray dataArray = list[2];
                QList<QByteArray> data = dataArray.split(',');
                _dataLen -= data.length();
                emit dataReceived(data);
            }
            break;
        }
    }
    else
    {
        QByteArray dataArray = list[0];
        QList<QByteArray> data = dataArray.split(',');
        int len = data.length() -1;
        if(data[len] == ""){
            data = data.mid(0,len);
        }
        if(data[0] == ""){
            data.mid(1,data.length());
        }

        if(data.length() > _dataLen){ //Last byteArray is header
            data = data.mid(0,_dataLen);
        }
        _dataLen -= data.length();
          emit dataReceived(data);
        if(_dataLen == 0){
            emit dataTransmitEnd();
        }
    }
}


void TcpServer::handleArduinoData(QList<QByteArray> list)
{
    //If arduino sends 1, motor has rotated
    int control = list[0].toInt();
    emit messageReceived("Arduino send: " +QString(control).toStdString());
    if(control == 1){
        emit stepperRotated();
    }
}

std::vector<QTcpSocket*> TcpServer::getSockets() const
{
    return _sockets;
}
