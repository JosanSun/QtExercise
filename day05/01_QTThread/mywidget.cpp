#include "mywidget.h"
#include "ui_mywidget.h"
#include <QThread>
#include <QDebug>

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);

    myTimer = new QTimer(this);

    //只要定时器启动，自动触发timeout()
    connect(myTimer, &QTimer::timeout, this, &MyWidget::dealTimeout);

    //分配空间
    thread = new MyThread(this);

    connect(thread, &MyThread::isDone, this, &MyWidget::dealDone);

    connect(this, &MyWidget::destroyed, this, &MyWidget::stopThread);
}

void MyWidget::dealTimeout(){
    static int i = 0;
    ++i;
    //设置lcd的值
    ui->lcdNumber->display(i);
}

void MyWidget::dealDone(){
    qDebug() << "This is done";
    myTimer->stop();
}

void MyWidget::stopThread(){
    //停止线程
    thread->quit();
    //等待线程处理完手头工作
    thread->wait();
}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::on_pushButton_clicked()
{
    //如果定时器没有工作   线程1，启动myTimer
    if(false == myTimer->isActive()){
        myTimer->start(100);
    }

    //启动线程，处理数据.  两个线程,执行sleep
    thread->start();

//    //非常复杂的数据处理，耗时较长
//    QThread::sleep(5);   //会出现无法响应的情况

//    //处理完数据后，关闭定时器
//    myTimer->stop();
//    qDebug() << "over";
}
