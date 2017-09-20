#include "widget.h"
#include "ui_widget.h"
#include <QHostAddress>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //分配空间，指定父对象
    udpSocket = new QUdpSocket(this);

    //绑定
    udpSocket->bind(1234);

    setWindowTitle("客户端端口为：1234");

    //当对方成功发送数据过来
    //自动触发 readyRead()
    connect(udpSocket, &QUdpSocket::readyRead, this, &Widget::dealMsg);
}

void Widget::dealMsg(){
    //读取对方发送的内容
    char buf[1024]={0};
    QHostAddress cliAddr;  //对方
    quint16 port;
    qint64 len = udpSocket->readDatagram(buf, sizeof(buf), &cliAddr, &port);
    if(0<len){
        //格式化
        QString str = QString("[%1:%2] %3")
                .arg(cliAddr.toString())
                .arg(port).arg(buf);
        //给编辑区设置内容
        ui->textEdit->setText(str);
    }
}

Widget::~Widget()
{
    delete ui;
}

//发送数据
void Widget::on_buttonSend_clicked()
{
    //先获取对方的IP和端口
    QString ip = ui->lineEditIP->text();
    quint16 port = ui->lineEditPort->text().toInt();

    //获取编辑区内容
    QString str = ui->textEdit->toPlainText();

    //给指定的IP发送数据
    udpSocket->writeDatagram(str.toUtf8(), QHostAddress(ip), port);
}
