#include "mywidget.h"
#include "ui_mywidget.h"
#include <QDebug>

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);

    //动态分配空间，不能指定父对象
    myT = new MyThread;  //NOTE:没有指定this,后面需要手动回收

    //创建子线程
    thread = new QThread(this);

    //把自定义线程加入到子线程中
    myT->moveToThread(thread);  //因为myT没有指定父对象，因此可以使用move..

    connect(myT, &MyThread::mySignal, this, &MyWidget::dealSignal);

    connect(this, &MyWidget::startThread, myT, &MyThread::myTimeout);

    connect(this, &MyWidget::destroyed, this, &MyWidget::dealClose);

    qDebug()<< "主线程号： "<<QThread::currentThread();

    //线程处理函数内部，不允许操作图形界面。只是纯数据处理

    //connect()第五个参数的作用
    //多线程时才有意义
    //默认的时候
    //如果是多线程，默认使用队列
    //如果是单线程，默认使用直接方式
    //队列：槽函数所在的线程和接收者一样
    //直接：槽函数所在的线程和发送者一样
}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::dealSignal(){
    static int i = 0;
    ++i;
    ui->lcdNumber->display(i);
}

void MyWidget::dealClose(){
    on_buttonStop_clicked();
    delete myT;
}

void MyWidget::on_buttonStart_clicked()
{
    if(thread->isRunning()){
        return ;
    }

    //启动线程，但是没有启动线程处理函数
    thread->start();
    myT->setFlag(false);
    //不能直接调用线程处理函数
    //直接调用，导致，线程处理函数和主线程在同一个线程
    //myT->myTimeout();


    //只能通过 signal - slot 方式调用
    emit startThread();
}

void MyWidget::on_buttonStop_clicked()
{
    if(false == thread->isRunning()){
        return ;
    }
    myT->setFlag(true);
    thread->quit();
    thread->wait();
}
