#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <memory>



class TcpServer : public QTcpServer
{
    Q_OBJECT
public:
    TcpServer();
    void sendMessage(std::string peerAddress, std::string message);
    void sendControl(std::string peerAddress, char key);
    std::vector<QTcpSocket* > getSockets() const;
    long getDataLen();


signals:
    /* We define specific keys to communication in order
     * to differentiate between the two clients (Android, Arduino)
     * and simple logmessages vs control signals
     */

    void messageReceived(std::string message);
    void removeIP(QString peeraddress);
    void dataReceived(QList<QByteArray> &data);
    void controlReceived(int control);
    void connectionReceived(std::string peerAddress);
    void dataTransmitEnd();
    void lengthReceived(int dataLen);
    void stepperRotated();


public slots:
    void onNewConnection();
    void onSocketStateChanged(QAbstractSocket::SocketState socketState);
    void onSendControl(std::string controlMessage);
    void onReadyRead();
    void updateSocketDeviceType(QString AndroidAddress, QString ArduinoAddress);


private:
    void handleAndroidData(QList<QByteArray> list);
    void handleArduinoData(QList<QByteArray> list);
    std::shared_ptr<QTcpSocket> _ServerSocket;
    std::vector<QTcpSocket *> _sockets;
    QString arduinoAddress;
    QString androidAddress;
    quint16 port{4242};

    int _dataLen = 0;

    /* TCP Data Packet Structure:
     * TCP HEADER (no edit)
     * Each part will be on seperate line
     * TCP KEY: for communication
     *      1 : Message
     *      2 : Data
     *
     *      Sender can be identified using QObject * sender and IP address
     *
     * TCP DATA SIZE: Length of DATA = length of lines.
     * TCP DATA: on seperate lines
     *
     */


};

#endif // TCPSERVER_H
