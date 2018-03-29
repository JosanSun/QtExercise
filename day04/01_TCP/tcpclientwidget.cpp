#include <QHostAddress>
#include <QPlainTextEdit>
#include <QDebug>

#include "tcpclientwidget.h"
#include "ui_tcpclientwidget.h"

TcpClientWidget::TcpClientWidget(QWidget *parent) :
    QWidget(parent), ui(new Ui::TcpClientWidget),
    tcpSocket(nullptr)
{
    ui->setupUi(this);
    setWindowTitle(tr("客户端"));
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
            });
    connect(tcpSocket, &QTcpSocket::disconnected,
            [=]()
            {
                tcpSocket->close();
                //tcpSocket = nullptr;
            });
}

TcpClientWidget::~TcpClientWidget()
{
    delete ui;
}

void TcpClientWidget::on_pushButtonConnect_clicked()
{
    QString ip = ui->lineEditIP->text();
    quint16 port = ui->lineEditPort->text().toInt();
    tcpSocket->connectToHost(QHostAddress(ip), port);
}

void TcpClientWidget::on_pushButtonSend_clicked()
{
    if(!tcpSocket)
    {
        qDebug() << "Client:tcpSocket is nullptr";
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
            qDebug() << "Client:输入窗口为空。";
        }
    }
    else
    {
        // 这里也可以设置清空发送栏
        qDebug() << "Client:tcpSocket is not nullptr, but is not open";
    }
}

void TcpClientWidget::on_pushButtonClose_clicked()
{
    if(tcpSocket->isOpen())
    {
        tcpSocket->disconnectFromHost();
    }
}

bool TcpClientWidget::isTextEditEmpty(const QPlainTextEdit* textEdit) const
{
    QString str = textEdit->toPlainText();
    return str.isEmpty();
}
