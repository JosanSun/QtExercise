#include <QDebug>
#include <QPlainTextEdit>
#include <QMessageBox>
#include <QNetworkProxy>
#include <QHostAddress>

#include "tcpserverwidget.h"
#include "ui_tcpserverwidget.h"

#define qcout qDebug()

TcpServerWidget::TcpServerWidget(QWidget *parent) :
    QWidget(parent), ui(new Ui::TcpServerWidget),
    tcpServer(nullptr), tcpSocket(nullptr)
{
    ui->setupUi(this);
    move(1100, 30);
    setFixedSize(400, 400);

    tcpServer = new QTcpServer(this);
    if(tcpServer)
    {
        // 未监听之前，TcpServer的端口号是0,地址为空 其他desciptor是最大值
        qcout << "tcpServer before assignment";
        qcout << "tcpServer max pending connections: "
              << tcpServer->maxPendingConnections();       // 30
        qcout << tcpServer->errorString();                 // null
        qcout << "tcpServer proxy information:";
        qcout << "hostName: " << tcpServer->proxy().hostName();  // null
        qcout << "passWord: " << tcpServer->proxy().password();  // null
        qcout << "user    : " << tcpServer->proxy().user();      // null
        qcout << "--------------------------";
        qcout << "Server address  : " << tcpServer->serverAddress().toString();   // null
        qcout << "Server Error    : " << tcpServer->serverError();                // UnknowSocketError
        qcout << "Server port     : " << tcpServer->serverPort();                 // 0
        qcout << "socket desciptor: " << tcpServer->socketDescriptor();           // -1

        // 如果没有指定服务器监听的端口，将采用一个随机数
        // if(!tcpServer->listen(QHostAddress::AnyIPv4))
        if(!tcpServer->listen(QHostAddress::LocalHost, 8888))
        {
            QMessageBox::critical(this, tr("TcpServer Example"),
                                  tr("Unable to start the server: %1.")
                                  .arg(tcpServer->errorString()));
            close();
        }

        // test tcpServer相关属性值
        qcout << "tcpServer max pending connections: "
              << tcpServer->maxPendingConnections();       // 30
        qcout << tcpServer->errorString();                 // null
        qcout << "tcpServer proxy information:";
        qcout << "hostName: " << tcpServer->proxy().hostName();  // null
        qcout << "passWord: " << tcpServer->proxy().password();  // null
        qcout << "user    : " << tcpServer->proxy().user();      // null
        qcout << "--------------------------";
        qcout << "Server address  : " << tcpServer->serverAddress().toString();   // 0.0.0.0        127.0.0.1
        qcout << "Server Error    : " << tcpServer->serverError();                // UnknowSocketError
        qcout << "Server port     : " << tcpServer->serverPort();                 // 8888
        qcout << "socket desciptor: " << tcpServer->socketDescriptor();           // 940            852 //每次运行都会获得一个不同的数值



        connect(tcpServer, &QTcpServer::newConnection,
                [=]()
        {
            qcout << "---------------------before connected -------------------";
            // 由于在connect之前，tcpSocket是nullptr。因此，不能调用这些内容
//            qcout << "tcpSocket error        : " << tcpSocket->error();                      // QAbstractSocket::UnknownSocketError
//            qcout << "tcpSocket local address: " << tcpSocket->localAddress().toString();    // ::ffff:127.0.0.1
//            qcout << "tcpSocket local port   : " << tcpSocket->localPort();                  // 8888
//            qcout << "pause mode             : " << tcpSocket->pauseMode();                  // QFlags()
//            qcout << "tcpSocket peer address : " << tcpSocket->peerAddress().toString();     // ::ffff:127.0.0.1
//            qcout << "tcpSocket peer address : " << tcpSocket->peerAddress().toIPv4Address();     // ::ffff:127.0.0.1
//            qcout << "tcpSocket peer address : " ;     // ::ffff:127.0.0.1
//            Q_IPV6ADDR add6 = tcpSocket->peerAddress().toIPv6Address();
//            for(int i = 0; i< 16; i+=4)
//            {
//                qcout << add6[i] << " " << add6[i + 1] << " " << add6[i + 2] << " " << add6[i + 3];
//            }
//            qcout << "tcpSocket peer port    : " << tcpSocket->peerPort();                   // 53013
//            qcout << "tcpSocket peer name    : " << tcpSocket->peerName();                   // null
//            qcout << "readBufferSize         : " << tcpSocket->readBufferSize();             // 0
//            qcout << "socketDescriptor       : " << tcpSocket->socketDescriptor();           // 1852
//            qcout << "socketOption           : " << tcpSocket->socketOption(QAbstractSocket::SocketOption()).toString();  // 0
//            qcout << "socketType             : " << tcpSocket->socketType();                 // QAbstractSocket::SocketType(TcpSocket)
//            qcout << "state                  : " << tcpSocket->state();                      // QAbstractSocket::ConnectedState

//            qcout << "tcpSocket proxy information:";
//            qcout << "hostName: " << tcpSocket->proxy().hostName();  // null
//            qcout << "passWord: " << tcpSocket->proxy().password();  // null
//            qcout << "user    : " << tcpSocket->proxy().user();      // null



            tcpSocket = tcpServer->nextPendingConnection();


            qcout << "-------------------- after connected -------------------";
            // test tcpSocket相关属性值
            qcout << "tcpSocket error        : " << tcpSocket->error();                           // QAbstractSocket::UnknownSocketError
            qcout << "tcpSocket local address: " << tcpSocket->localAddress().toString();         // ::ffff:127.0.0.1
            qcout << "tcpSocket local port   : " << tcpSocket->localPort();                       // 8888
            qcout << "pause mode             : " << tcpSocket->pauseMode();                       // QFlags()
            qcout << "tcpSocket peer address : " << tcpSocket->peerAddress().toString();          // ::ffff:127.0.0.1
            qcout << "tcpSocket peer address : " << tcpSocket->peerAddress().toIPv4Address();     // 2130706433 = 0xFF00 0001
            qcout << "tcpSocket peer address : " ;     // ::ffff:127.0.0.1
            Q_IPV6ADDR add6_1 = tcpSocket->peerAddress().toIPv6Address();
            for(int i = 0; i< 16; i+=4)
            {
                qcout << add6_1[i] << " " << add6_1[i + 1] << " " << add6_1[i + 2] << " " << add6_1[i + 3];
            }
            qcout << "tcpSocket peer port    : " << tcpSocket->peerPort();                   // 53013
            qcout << "tcpSocket peer name    : " << tcpSocket->peerName();                   // null
            qcout << "readBufferSize         : " << tcpSocket->readBufferSize();             // 0
            qcout << "socketDescriptor       : " << tcpSocket->socketDescriptor();           // 1852
            qcout << "socketOption           : " << tcpSocket->socketOption(QAbstractSocket::SocketOption()).toString();  // 0
            qcout << "socketType             : " << tcpSocket->socketType();                 // QAbstractSocket::SocketType(TcpSocket)
            qcout << "state                  : " << tcpSocket->state();                      // QAbstractSocket::ConnectedState

            qcout << "tcpSocket proxy information:";
            qcout << "hostName: " << tcpSocket->proxy().hostName();  // null
            qcout << "passWord: " << tcpSocket->proxy().password();  // null
            qcout << "user    : " << tcpSocket->proxy().user();      // null





            QString ip = tcpSocket->peerAddress().toString();
            quint16 port = tcpSocket->peerPort();
            ui->plainTextEditRead->setPlainText(tr("与服务器连接成功\n"
                                                   "服务器的地址是：[ %1: %2 ]").arg(tcpSocket->localAddress().toString())
                                                .arg(tcpSocket->localPort()));
            ui->plainTextEditRead->appendPlainText(tr("客户端的地址是：[ %1: %2 ]")
                                                .arg(ip).arg(port));

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
        qDebug() << "Cannot allocate the TCP server socket";
    }

}

TcpServerWidget::~TcpServerWidget()
{
    delete ui;
}

void TcpServerWidget::on_pushButtonSend_clicked()
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

void TcpServerWidget::on_pushButtonClose_clicked()
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

bool TcpServerWidget::isTextEditEmpty(const QPlainTextEdit* textEdit) const
{
    QString str = textEdit->toPlainText();
    return str.isEmpty();
}
