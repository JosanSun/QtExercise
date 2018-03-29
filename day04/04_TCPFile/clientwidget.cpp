#include <QDebug>
#include <QMessageBox>
#include <QHostAddress>

#include "clientwidget.h"
#include "ui_clientwidget.h"

ClientWidget::ClientWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientWidget)
{
    ui->setupUi(this);

    setWindowTitle(tr("客户机"));

    tcpSocket = new QTcpSocket(this);
    isStart = true;
    ui->progressBar->setValue(0);
    connect(tcpSocket, &QTcpSocket::readyRead,
            [=]()
            {
               // 取出接收的内容
               QByteArray buf = tcpSocket->readAll();
               if(true == isStart)
               {
                   isStart = false;

                   fileName = QString(buf).section("##", 0, 0);
                   fileSize = QString(buf).section("##", 1, 1).toInt();
                   recvSize = 0;

                   file.setFileName(fileName);
                   bool isOk = file.open(QIODevice::WriteOnly);
                   if(false == isOk)
                   {
                       qDebug() << "WriteOnly error 40";
                   }
               }
               else
               {
                   qint64 len = file.write(buf);

                   recvSize += len;
                   if(recvSize == fileSize)
                   {
                       file.close();
                       QMessageBox::information(this, tr("传输完成"),
                                                tr("文件接收完成"));
                       tcpSocket->disconnectFromHost();
                       tcpSocket->close();
                   }
                   int progress = static_cast<int>(static_cast<double>(recvSize) / fileSize * 100);
                   ui->progressBar->setValue(progress);
               }
            });
}

ClientWidget::~ClientWidget()
{
    delete ui;
}

void ClientWidget::on_buttonConnect_clicked()
{
    QString ip = ui->lineEditIP->text();
    quint16 port = ui->lineEditPort->text().toInt();

    tcpSocket->connectToHost(QHostAddress(ip), port);
}
