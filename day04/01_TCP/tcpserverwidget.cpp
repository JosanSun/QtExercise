#include <QDebug>
#include <QPlainTextEdit>

#include "tcpserverwidget.h"
#include "ui_tcpserverwidget.h"

TcpServerWidget::TcpServerWidget(QWidget *parent) :
    QWidget(parent), ui(new Ui::TcpServerWidget),
    tcpServer(nullptr), tcpSocket(nullptr)
{
    ui->setupUi(this);
    setWindowTitle(tr("服务器（端口号：8888）"));
    move(1100, 30);
    setFixedSize(400, 400);

    tcpServer = new QTcpServer(this);
    if(tcpServer)
    {
        tcpServer->listen(QHostAddress::Any, 8888);

        connect(tcpServer, &QTcpServer::newConnection,
                [=]()
        {
            tcpSocket = tcpServer->nextPendingConnection();
            QString ip = tcpSocket->peerAddress().toString();
            quint16 port = tcpSocket->peerPort();
            ui->plainTextEditRead->setPlainText(tr("[ %1:%2 ]: 连接成功")
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
    if(!tcpSocket)
    {
        qDebug() << "Server:tcpSocket is nullptr";
        return;
    }
    if(tcpSocket->isOpen())
    {
        if(!isTextEditEmpty(ui->plainTextEditWrite))
        {
            QString sendData = ui->plainTextEditWrite->toPlainText();
            tcpSocket->write(sendData.toUtf8());
            ui->plainTextEditWrite->clear();
        }
        else
        {
            qDebug() << tr("Server:输入窗口为空。");
        }
    }
    else
    {
        // 这里也可以设置清空发送栏
        qDebug() << "Server:tcpSocket is not nullptr, but is not open";
    }
}

void TcpServerWidget::on_pushButtonClose_clicked()
{
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
