#include "clienwidget.h"
#include "ui_clienwidget.h"
#include <QDebug>
#include <QMessageBox>
#include <QHostAddress>
ClienWidget::ClienWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClienWidget)
{
    ui->setupUi(this);
    isStart = true;
    tcpSocket = new QTcpSocket(this);
    setWindowTitle("客户端");
    connect(tcpSocket, &QTcpSocket::readyRead,
            [=]()
            {
                //取出接收的内容
                QByteArray buf = tcpSocket->readAll();
                if(isStart){
                    //接收头
                    isStart = false;
                    //解析头信息   buf = "hello##1024"
                    //初始化
                    fileName = QString(buf).section("##", 0, 0);
                    fileSize = QString(buf).section("##", 1, 1).toInt();
                    recvSize = 0;

                    //打开文件
                    file.setFileName(fileName);

                    bool isOk = file.open(QIODevice::WriteOnly);
                    if(false == isOk){
                        qDebug()<<"WriteOnly error 40";
                    }
                }
                //文件信息
                else{
                    qint64 len = file.write(buf);
                    recvSize += len;

                    if(recvSize == fileSize){
                        file.close();
                        QMessageBox::information(this, "完成", "文件接收完成");
                        tcpSocket->disconnectFromHost();
                        tcpSocket->close();

                    }
                }
            }
            );

}

ClienWidget::~ClienWidget()
{
    delete ui;
}

void ClienWidget::on_buttonConnect_clicked()
{
    //获取服务器ip和端口
    QString ip = ui->lineEditIP->text();
    quint16 port = ui->lineEditPort->text().toInt();

    //主动和服务器建立连接
    tcpSocket->connectToHost(QHostAddress(ip), port);
}
