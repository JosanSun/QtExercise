#include <QHostAddress>

#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    setWindowTitle(tr("服务器端口：8888"));

    udpSocket = new QUdpSocket(this);
    //udpSocket->bind(8888);
    udpSocket->bind(QHostAddress::AnyIPv4, 8888);

    udpSocket->joinMulticastGroup(QHostAddress("224.0.0.2"));
    //udpSocket->leaveMulticastGroup(QHostAddress("224.0.0.2"));


    connect(udpSocket, &QUdpSocket::readyRead, this, &Widget::dealMsg);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::dealMsg()
{
    char buf[1024] = {0};
    QHostAddress address;
    quint16 port;
    qint64 len = udpSocket->readDatagram(buf, sizeof(buf), &address, &port);
    if(len > 0)
    {
        // 格式化
        QString str = QString("[%1:%2] %3")
                .arg(address.toString())
                .arg(port)
                .arg(buf);
        ui->textEdit->setText(str);
    }
}

void Widget::on_buttonSend_clicked()
{
    QString ip = ui->lineEditIP->text();
    quint16 port = ui->lineEditPort->text().toInt();

    QString str = ui->textEdit->toPlainText();
    udpSocket->writeDatagram(str.toUtf8(), QHostAddress(ip), port);

}

void Widget::on_buttonClose_clicked()
{
    udpSocket->disconnectFromHost();
    udpSocket->close();
}
