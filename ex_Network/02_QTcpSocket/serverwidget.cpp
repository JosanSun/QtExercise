#include <QDebug>
#include <QPlainTextEdit>
#include <QMessageBox>
#include <QNetworkProxy>
#include <QHostAddress>

#include "ServerWidget.h"
#include "ui_ServerWidget.h"

#define qcout qDebug()

ServerWidget::ServerWidget(QWidget *parent) :
    QWidget(parent), ui(new Ui::ServerWidget),
    tcpServer(nullptr), tcpSocket(nullptr)
{
    ui->setupUi(this);
    move(1100, 30);
    setFixedSize(400, 400);

    tcpServer = new QTcpServer(this);
    if(tcpServer)
    {
        if(!tcpServer->listen(QHostAddress::AnyIPv4, 8888))
        {
            QMessageBox::critical(this, tr("TcpServer Example"),
                                  tr("Unable to start the server: %1.")
                                  .arg(tcpServer->errorString()));
            close();
        }
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
            qcout << "tcpSocket peer port    : " << tcpSocket->peerPort();                   // 53013  // 随机数
            qcout << "tcpSocket peer name    : " << tcpSocket->peerName();                   // null
            // 返回QTcpSocket的暂停模式
            qcout << "pause mode             : " << tcpSocket->pauseMode();                       // QFlags()
            // 返回内部读缓冲的大小。如果为0, 表示没有大小限制，即确保所有的数据都能接收
            qcout << "readBufferSize         : " << tcpSocket->readBufferSize();             // 0
            // 返回本地的socket描述符，也就是一个int32或int64的数。如果没有，则返回-1.
            qcout << "socketDescriptor       : " << tcpSocket->socketDescriptor();           // 1852   // 随机数
            // 返回选项的值
            qcout << "socketOption           : " << tcpSocket->socketOption(QAbstractSocket::SocketOption()).toString();  // 0
            // 返回socket的类型（TCP, UDP或者其他）
            qcout << "socketType             : " << tcpSocket->socketType();                 // QAbstractSocket::SocketType(TcpSocket)
            // 返回socket的状态信息
            qcout << "state                  : " << tcpSocket->state();                      // QAbstractSocket::ConnectedState


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
    }

    else
    {
        qcout << "Cannot allocate the TCP server socket";
    }
}
ServerWidget::~ServerWidget()
{
    delete ui;
}

void ServerWidget::on_pushButtonSend_clicked()
{
    // possible errors
    if(!tcpSocket)
    {
        qDebug() << "Server:tcpSocket is nullptr";
        return;
    }
    if(!tcpSocket->isOpen())
    {
        qcout << "Server:tcpSocket is not nullptr, but is not open";
        return ;
    }
    if(isTextEditEmpty(ui->plainTextEditWrite))
    {
        qDebug() << tr("Server:输入窗口为空。");
        return ;
    }

    QString sendData = ui->plainTextEditWrite->toPlainText();
    tcpSocket->write(sendData.toUtf8());
    ui->plainTextEditWrite->clear();
}

void ServerWidget::on_pushButtonClose_clicked()
{
    // 不可以多次关闭close  diconnectFromHost()
    //    for(int i = 0; i < 5; ++i)
    //    {
    //        tcpSocket->disconnectFromHost();
    //        //tcpSocket->close();
    //    }
    //    //tcpSocket->close();
    if(tcpSocket)
    {
        tcpSocket->disconnectFromHost();
    }
}

bool ServerWidget::isTextEditEmpty(const QPlainTextEdit* textEdit) const
{
    QString str = textEdit->toPlainText();
    return str.isEmpty();
}
