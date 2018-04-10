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
