/**
 *  Josan学QT网络编程01-QTcpServer
 *  先学QTcpServer, 快速了解QTcpServer的常用接口。
 *  暂时不需要了解的类QHostAddress, QNetworkProxy, QTcpSocket
 */

// main-tcpServer.cpp
// 通过对QTcpServer的常用接口的调用来，熟悉QTcpServer的使用方法
// 重点掌握 serverAddress(), serverPort(), listen(), nextPendingConnection(), close()的用法

#include <QTcpServer>
#include <QHostAddress>
#include <QTcpSocket>
#include <QDebug>
#include <QNetworkProxy>

#define qcout qDebug()

int main(void)
{
    // 创建tcp的监听套接字
    QTcpServer* tcpServer = new QTcpServer;

    // QString QTcpServer::errorString() const
    // Returns a human readable description of the last error that occurred.
    // 返回为空，表示没有出错。
    qcout << tcpServer->errorString();              // null

    qcout << tcpServer->serverAddress().toString(); // null   还没有监听，因此服务器的地址为空
    qcout << tcpServer->serverPort();               // 0      还没有监听，因此服务器的端口为空
    // tcpServer->listen(QHostAddress::AnyIPv4);  // 常用QHostAddress::AnyIPv4，尽量少用QHostAddress::Any.因为Any会同时监听IPv6的地址，可能会产生冲突。
    // bool QTcpServer::listen(const QHostAddress &address = QHostAddress::Any, quint16 port = 0)
    // Tells the server to listen for incoming connections on address address and port port. If port is 0, a port is chosen automatically.
    // If address is QHostAddress::Any, the server will listen on all network interfaces. 包括IPv4和IPv6
    if(tcpServer->listen(QHostAddress::AnyIPv4))
    {
        // bool QTcpServer::isListening() const
        // Returns true if the server is currently listening for incoming connections; otherwise returns false.
        qcout << "TcpServer is isListening: " << tcpServer->isListening();   // true 现在正在监听

        // int QTcpServer::maxPendingConnections() const
        // Returns the maximum number of pending accepted connections. The default is 30.
        qcout << "maxPendingConnections is: " << tcpServer->maxPendingConnections(); // 30

        // [virtual] QTcpSocket *QTcpServer::nextPendingConnection()
        // Returns the next pending connection as a connected QTcpSocket object.
        // 常常利用这个函数来获得一个新的QTcpSocket对象，然后利用这个对象来进行数据的通信。这个socket也叫做通信套接字。
        QTcpSocket* tcpSocket = tcpServer->nextPendingConnection();
        qcout << (tcpSocket ? "TcpSocket is not null" : "TcpSocket is null");       // TcpSocket is null   说明现在没有tcp进行连接。

        // QNetworkProxy QTcpServer::proxy() const
        // Returns the network proxy for this socket. By default QNetworkProxy::DefaultProxy is used.
        QNetworkProxy proxy = tcpServer->proxy();   // 获取tcp服务器的网络代理信息


        // QHostAddress QTcpServer::serverAddress() const
        // Returns the server's address if the server is listening for connections; otherwise returns QHostAddress::Null.
        qcout << "tcpServer address is: " << tcpServer->serverAddress().toString();   // "0.0.0.0"    返回服务器正在监听的地址
        // quint16 QTcpServer::serverPort() const
        // Returns the server's port if the server is listening for connections; otherwise returns 0.
        qcout << "tcpServer port    is: " << tcpServer->serverPort();                 // 8888         返回服务器正在监听的端口号;如果服务器listen()时，没有指定端口号，则会返回一个随机的端口号。 eg:11662
        // QAbstractSocket::SocketError QTcpServer::serverError() const
        // Returns an error code for the last error that occurred.
        qcout << "tcpServer error   is: " << tcpServer->serverError();                 // QAbstractSocket::UnknownSocketError  数值为-1. 默认的返回值

        // bool QTcpServer::waitForNewConnection(int msec = 0, bool *timedOut = Q_NULLPTR)
        // Waits for at most msec milliseconds or until an incoming connection is available.
        // Returns true if a connection is available; otherwise returns false. If the operation timed out and timedOut is not 0, *timedOut will be set to true.
        if(tcpServer->waitForNewConnection(5000))
        {
            qcout << "tcpServer is waiting for new connection";
        }
        else
        {
            qcout << "tcpServer is not waiting for new connection";  // tcpServer is not waiting for new connection   由于没有连接接入，因此没有等待新的连接。
        }
    }
    else
    {
        qcout << "tcpServer is not listening";
    }

    tcpServer->close();

    qcout << "TcpServer is isListening: " << tcpServer->isListening();   // false     tcpServer已经停止监听


    return 0;
}
