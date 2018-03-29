#include <QHostAddress>

#include "clientwidget.h"
#include "ui_clientwidget.h"

ClientWidget::ClientWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientWidget)
{
    ui->setupUi(this);

    setWindowTitle(tr("客户端端口：12345"));

    udpSocket = new QUdpSocket(this);
    udpSocket->bind(12345);

    connect(udpSocket, &QUdpSocket::readyRead, this, &ClientWidget::dealMsg);
}

ClientWidget::~ClientWidget()
{
    delete ui;
}

void ClientWidget::dealMsg()
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

void ClientWidget::on_buttonSend_clicked()
{
    QString ip = ui->lineEditIP->text();
    quint16 port = ui->lineEditPort->text().toInt();

    QString str = ui->textEdit->toPlainText();
    udpSocket->writeDatagram(str.toUtf8(), QHostAddress(ip), port);

}

void ClientWidget::on_buttonClose_clicked()
{
    udpSocket->disconnectFromHost();
    udpSocket->close();
}
