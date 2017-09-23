#ifndef CLIENWIDGET_H
#define CLIENWIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QFile>

namespace Ui {
class ClienWidget;
}

class ClienWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClienWidget(QWidget *parent = 0);
    ~ClienWidget();

private slots:
    void on_buttonConnect_clicked();

private:
    Ui::ClienWidget *ui;

    QTcpSocket* tcpSocket;  //通信套接字

    QFile file;   //文件对象
    QString fileName;  //文件名字
    qint64 fileSize;   //文件大小
    qint64 recvSize;   //已经接收文件大小

    bool isStart;
};

#endif // CLIENWIDGET_H
