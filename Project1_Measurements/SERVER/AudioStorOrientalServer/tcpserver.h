#ifndef TCPSERVER_H
#define TCPSERVER_H
#include <QTcpSocket>
#include <QtNetwork>
#include <QDialog>



class TcpServer : public QDialog
{
    Q_OBJECT
public:
    TcpServer(const QHostAddress &address, const quint16 port);
    TcpServer(const quint16 port);
    ~TcpServer();
    bool startServer();
    QHostAddress getServerAddress() const;
    quint16 getServerPort();
    static std::vector<QHostAddress> getLocalAddresses();

    int getIndex() const;

signals:
    void packetReceived(const QHostAddress &peerAddress, const quint16 peerport);

private slots:
    void sessionOpened();
    // Once filename is created this slot is called to write received data into the file
    void receiveData();
    // Receive the size of the String filename (fixed with 1 byte) and afterwards its filename
    void receiveFileName();
    void connect();

private:
    QTcpServer * tcpServer;
    QTcpSocket * serverSocket;
    QNetworkSession * networkSession;

    QString foldername = "D:/Master/Thesis/Development/Data";
    QString filenameAppend;
};


#endif // TCPSERVER_H
