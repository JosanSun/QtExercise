# Josan学QT网络编程02-QTcpSocket  

## 导读  
**PS:** 如果你在之前的文章，看过导读，那么你可以跳过这段的阅读。如果没有看过导读，我建议你耐心的看完。这样有助于你更快的获取新知识。  

- 文章编写的整体思路  
先简单描述一下某个类，一般以QT官网的''Detalied Description"为主；  
然后是自己测试这个类的接口所用到的测试函数。测试函数的有测试结果说明以及对某个函数的**解释说明**。强烈建议你，自己跑一下测试函数，光看的话，印象是不深刻的。  
最后，送上一些参考链接，代码下载地址，以及自己的学习群：676908519。欢迎爱分享的小伙伴入群交流讨论。  
翻译说明：  
1. 对于一些常用的专业词汇，尽量不翻译，使用英文说明。  
2. 对于自己把握不是很准备的语句，会选择性跳过。  
3. 本翻译不是默守陈规式的翻译，对于一些语句翻译，会追加一些个人心得的补充。  

## QTcpSocket

[官方文档翻译](http://doc.qt.io/qt-5/qtcpsocket.html#details)


QTcpSocket提供了一个TCP套接字。  
TCP提供一个可靠的，面向字节的，面向连接的传输协议。它尤其适用于连续性传输数据。  
QTcpSocket是QAstractSocket的子类。在建立TCP连接，传输数据流的时候，QTcpSocket显得十分方便。更多信息，可以参考[QAbstractSocket](http://doc.qt.io/qt-5/qabstractsocket.html)文档说明  
注意：TCP套接字不能以QIODevice::Unbuffered的模式打开，TCP套接字必须使用缓存


- // 服务端主体代码
``` C++
/**
 *  Josan学QT网络编程02-QTcpSocket
 */

connect(tcpServer, &QTcpServer::newConnection,
        [=]()
{
    qcout << "---------------------before connected -------------------";
    // 由于在connect之前，tcpSocket是nullptr。因此，不能调用这些内容QTcpSocket提供的接口

    tcpSocket = tcpServer->nextPendingConnection();

    qcout << "-------------------- after connected -------------------";
    // test tcpSocket相关属性值
    // error信号，还有信号信息
    qcout << "tcpSocket error        : " << tcpSocket->error();                           // QAbstractSocket::UnknownSocketError
    // 本地的地址和端口
    qcout << "tcpSocket local address: " << tcpSocket->localAddress().toString();         // 127.0.0.1
    qcout << "tcpSocket local port   : " << tcpSocket->localPort();                       // 8888
    // 对方的地址、端口和名字
    qcout << "tcpSocket peer address : " << tcpSocket->peerAddress().toString();          // 127.0.0.1
    qcout << "tcpSocket peer port    : " << tcpSocket->peerPort();                        // 53013  // 随机数
    qcout << "tcpSocket peer name    : " << tcpSocket->peerName();                        // null
    // 返回QTcpSocket的暂停模式
    qcout << "pause mode             : " << tcpSocket->pauseMode();                       // QFlags()
    // 返回内部读缓冲的大小。如果为0, 表示没有大小限制，即确保所有的数据都能接收
    qcout << "readBufferSize         : " << tcpSocket->readBufferSize();                   // 0
    // 返回本地的socket描述符，也就是一个int32或int64的数。如果没有，则返回-1.
    qcout << "socketDescriptor       : " << tcpSocket->socketDescriptor();                 // 1852   // 随机数
    // 返回选项的值
    qcout << "socketOption           : " << tcpSocket->socketOption(QAbstractSocket::SocketOption()).toString();  // 0
    // 返回socket的类型（TCP, UDP或者其他）
    qcout << "socketType             : " << tcpSocket->socketType();                       // QAbstractSocket::SocketType(TcpSocket)
    // 返回socket的状态信息
    qcout << "state                  : " << tcpSocket->state();                            // QAbstractSocket::ConnectedState


    QNetworkProxy proxy = tcpSocket->proxy();
    tcpSocket->setProxy(QNetworkProxy::NoProxy);
    qcout << "tcpSocket proxy information:";
    qcout << "hostName: " << tcpSocket->proxy().hostName();  // null
    qcout << "passWord: " << tcpSocket->proxy().password();  // null
    qcout << "user    : " << tcpSocket->proxy().user();      // null

    // -----------忽略部分start--------------------
    QString ip = tcpSocket->peerAddress().toString();
    quint16 port = tcpSocket->peerPort();
    ui->plainTextEditRead->setPlainText(tr("与服务器连接成功\n"
                                           "服务器的地址是：[ %1: %2 ]").arg(tcpSocket->localAddress().toString())
                                        .arg(tcpSocket->localPort()));
    ui->plainTextEditRead->appendPlainText(tr("客户端的地址是：[ %1: %2 ]")
                                           .arg(ip).arg(port));
    // -----------忽略部分end--------------------

    connect(tcpSocket, &QTcpSocket::readyRead,
            [=]()
    {
        QByteArray dataArray = tcpSocket->readAll();
        ui->plainTextEditRead->appendPlainText(dataArray);
    });

    connect(tcpSocket, &QTcpSocket::disconnected,
            [=]()
    {
        tcpSocket->close();
        tcpSocket = nullptr;
    });
});
```

- // 客户端主体代码
``` C++
/**
 *  Josan学QT网络编程02-QTcpSocket
 *  connectToHost(), disconnectFromHost(), 以及当做IO设备的write, read, readAll等函数
 */

#include <QHostAddress>
#include <QPlainTextEdit>
#include <QDebug>

#define qcout qDebug()

#include "ClientWidget.h"
#include "ui_ClientWidget.h"

ClientWidget::ClientWidget(QWidget *parent) :
    QWidget(parent), ui(new Ui::ClientWidget),
    tcpSocket(nullptr)
{
    ui->setupUi(this);

    move(700, 30);
    setFixedSize(400, 400);

    tcpSocket = new QTcpSocket(this);

    connect(tcpSocket, &QTcpSocket::readyRead,
            [=]()
            {
                QByteArray dataReceive = tcpSocket->readAll();
                ui->plainTextEditRead->appendPlainText(QString(dataReceive));
            });
    connect(tcpSocket, &QTcpSocket::connected,
            [=]()
            {
                ui->plainTextEditRead->setPlainText(tr("已成功连接服务器"));
                QString ip = tcpSocket->peerAddress().toString();
                quint16 port = tcpSocket->peerPort();
                ui->plainTextEditRead->appendPlainText(tr("服务器的IP地址：%1\n端口号：%2\n")
                                            .arg(ip).arg(port));
                ui->plainTextEditRead->appendPlainText(tr("本  机的IP地址：%1\n端口号：%2\n")
                                                       .arg(tcpSocket->localAddress().toString())
                                                       .arg(tcpSocket->localPort()));
            });
    connect(tcpSocket, &QTcpSocket::disconnected,
            [=]()
            {
                tcpSocket->close();
                //tcpSocket = nullptr;
            });
}

ClientWidget::~ClientWidget()
{
    delete ui;
}

void ClientWidget::on_pushButtonConnect_clicked()
{
    if(tcpSocket->isOpen())
    {
        qcout << "The server is already connected.\nDon't connect again.";
        return ;
    }
    QString ip = ui->lineEditIP->text();
    quint16 port = ui->lineEditPort->text().toInt();
    tcpSocket->connectToHost(QHostAddress(ip), port);
}

void ClientWidget::on_pushButtonSend_clicked()
{
    if(!tcpSocket)
    {
        qcout << "Client:tcpSocket is nullptr";
        return;
    }

    if(tcpSocket->isOpen())
    {
        if(!isTextEditEmpty(ui->plainTextEditWrite))
        {
            QString sendData = ui->plainTextEditWrite->toPlainText();
            tcpSocket->write(sendData.toUtf8().data());
            ui->plainTextEditWrite->clear();
        }
        else
        {
            qcout << "Client:输入窗口为空。";
        }
    }
    else
    {
        // 这里也可以设置清空发送栏
        qcout << "Client:tcpSocket is not nullptr, but is not open";
    }
}

void ClientWidget::on_pushButtonClose_clicked()
{
    if(tcpSocket->isOpen())
    {
        tcpSocket->disconnectFromHost();
    }
}

bool ClientWidget::isTextEditEmpty(const QPlainTextEdit* textEdit) const
{
    QString str = textEdit->toPlainText();
    return str.isEmpty();
}

```


## 附件

1. [QTcpSocket官方文档](http://doc.qt.io/qt-5/qtcpsocket.html "qt5.10")
2. [源代码链接下载](https://download.csdn.net/download/lizi_stdio/10339445)
3.  Josan Qt学习群：676908519