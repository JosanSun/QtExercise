# Josan学QT网络编程

## 导读
**PS:** 如果你在之前的文章，看过导读，那么你可以跳过这段的阅读。如果没有看过导读，我建议你耐心的看完。这样有助于你更快的获取新知识。

- 文章编写的整体思路
先简单描述一下某个类，一般以QT官网的''Detalied Description"为主；  
然后是自己测试这个类的接口所用到的测试函数。测试函数的有测试结果说明以及对某个函数的**解释说明**。强烈建议你，自己跑一下测试函数，光看的话，印象是不深刻的。  
最后，送上一些参考链接，代码下载地址，以及自己的学习群：676908519。欢迎爱分享的小伙伴入群交流讨论。

## QTcpServer

[官方文档翻译](http://doc.qt.io/qt-5/qtcpserver.html#details)
翻译说明：
1. 对于一些常用的专业词汇，尽量不翻译，使用英文说明。
2. 对于自己把握不是很准备的语句，会选择性跳过。
3.  本翻译不是默守陈规式的翻译，对于一些语句翻译，会追加一些个人心得的补充。

QTcpServer提供了一个以TCP为基础的服务器类。

这个类可以accept即将到来的TCP的连接。**对于port**，你可以指定QTcpServer的端口，或者让QTcpServer自动获得一个端口号。**对于IP地址**，你可以指定QTcpServer的监听地址，或者在所有机器的IP地址上面进行监听。

调用`listen()`可以让服务器去监听即将到来的连接。如果有一个客户机连接到服务器，那么QTcpServer就会每次发送一个`newConnection()`信号。

调用`nextPendingConnection()`来获取一个已经连接上的QTcpSocket。这个函数返回的一个QTcpSocket指针。

如果一个错误发生，`serverError()`返回错误的类型，同时`errorString()`返回一个QString，这个QString可以获得一个阅读性更好的错误描述。

当QTcpServer正在监听的连接的时候，可以通过`serverAddress()`和`serverPort()`来获得服务器正在监听的IP地址和端口号。

调用`close()`可以使QTcpServer停止监听。

尽管QTcpServer使用时，伴随着一个event loop，但是还是有可能不是使用事件循环。那种情况下，你必须使用`waitForNewConnection()`。这个函数可以阻塞event loop，直到一个新的连接到来或者传入`waitForNewConnection()`的时间超过了（eg：比如传入5s, 在5s之前，QTcpServer不会使用事件循环；5s之后, QTcpServer又会使用事件循环）。

``` C++
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
        if(tcpServer->waitForNewConnection(2000))
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

```

## 附件

1. [QTcpServer官方文档](http://doc.qt.io/qt-5/qtcpserver.html "qt5.10")
2. [源代码链接下载](https://download.csdn.net/download/lizi_stdio/10331778)
3.  Josan Qt学习群：676908519