#include <QHostAddress>
#include <QFile>
#include <QFileInfo>
#include <QTimer>
#include <QFileDialog>
#include <QDebug>
#include <QTimer>

#include "serverwidget.h"
#include "ui_serverwidget.h"

ServerWidget::ServerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerWidget)
{
    ui->setupUi(this);
    setWindowTitle(tr("服务器：8888"));
    ui->buttonFile->setEnabled(false);
    ui->buttonSend->setEnabled(false);
    tcpServer = new QTcpServer(this);
    tcpServer->listen(QHostAddress::Any, 8888);
    connect(tcpServer, &QTcpServer::newConnection,
            [=]()
            {
                tcpSocket = tcpServer->nextPendingConnection();
                QString ip = tcpSocket->peerAddress().toString();
                quint16 port = tcpSocket->peerPort();
                QString str = tr("[%1%:%2]和服务器连接成功").arg(ip).arg(port);
                ui->textEdit->setText(str);
                ui->buttonFile->setEnabled(true);
            });
    connect(&timer, &QTimer::timeout,
            [=]()
            {
                timer.stop();
                sendData();
            });
}

ServerWidget::~ServerWidget()
{
    delete ui;
}

void ServerWidget::on_buttonFile_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "open", "../");
    if(filePath.isEmpty())
    {
        qDebug() << tr("选择文件路径出错 62");
        return ;
    }

    QFileInfo fileInfo(filePath);
    fileName = fileInfo.fileName();
    fileSize = fileInfo.size();
    sendSize = 0;

    file.setFileName(filePath);
    bool isOk = file.open(QIODevice::ReadOnly);
    if(false == isOk)
    {
        qDebug() << tr("只读的方式打开文件失败 77");
    }

    ui->textEdit->append(filePath);

    ui->buttonFile->setEnabled(false);
    ui->buttonSend->setEnabled(true);
}

void ServerWidget::on_buttonSend_clicked()
{
    //先发送文件头信息
    QString head = QString("%1##%2").arg(fileName).arg(fileSize);
    qint64 len = tcpSocket->write(head.toUtf8());
    if(len > 0)
    {
        timer.start(20);
    }
    else
    {
        qcout << "头部信息发送失败 110";
        file.close();
        ui->buttonFile->setEnabled(true);
        ui->buttonSend->setEnabled(false);
    }

    //发送真正的文件信息
}


void ServerWidget::sendData()
{
    qint64 len = 0;
    do
    {
        char buf[4 * 1024] = {0};
        len = 0;
        // 往文件中读数据
        len = file.read(buf, sizeof(buf));
        // 发送数据，读多少，发多少
        len = tcpSocket->write(buf, len);

        sendSize += len;
    }while(len > 0);

    if(sendSize == fileSize)
    {
        ui->textEdit->append("文件发送完毕");
        file.close();

        tcpSocket->disconnectFromHost();
        tcpSocket->close();
    }
}
