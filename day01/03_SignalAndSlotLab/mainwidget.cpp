#include "mainwidget.h"
#include <QDebug>    //打印

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent),  sub(parent)
{
    b1.setParent(this);
    b1.setText("close");
    b1.move(100, 100);

    b2 = new QPushButton(this);
    b2->setText("123");

    setWindowTitle(QString::fromLocal8Bit("老大"));

    b3.setParent(this);
    b3.setText(QString::fromLocal8Bit("切换到子窗口"));
    b3.move(50, 50);


    //如何新建窗口，右击->添加新文件->c++->c++ class
    //sub.show();

    connect(&b3, &QPushButton::released, this, &MainWidget::changeWindow);

    //信号函数重载的话，可以使用函数指针进行区分

//    void (SubWidget::*ptr)() = &SubWidget::mySignal;
//    void (SubWidget::*ptr1)(int, QString) = &SubWidget::mySignal;

//    connect(&sub, ptr, this, &MainWidget::changeWindow2);
//    connect(&sub, ptr1, this, &MainWidget::dealSlot);

    //Qt4信号连接
    //Qt4槽函数必须有slots关键字来修饰
    //采用宏定义的方式进行调用
    connect(&sub, SIGNAL(mySingnal()), this, SLOT(changeWindow2()));
    connect(&sub, SIGNAL(mySignal(int,QString)), this,
                    SLOT(dealSlot(int,QString)));


    resize(400, 300);
}

void MainWidget::dealSlot(int a, QString b){
    qDebug()<<a<<"  "<<b;


//    QString str = "我是中国人";
//    //输出中文没有成功。
//    //str.toUtf8() -> 字节数组QByteArray
//    //......data() -> 将直接数组转为char*

//    qDebug()<<str.toUtf8().data();
}

void MainWidget::changeWindow(){
    //子窗口显示，主窗口隐藏
    this->hide();
    sub.show();
}

void MainWidget::changeWindow2(){
    //主窗口显示，子窗口隐藏
    show();
    sub.hide();
}

MainWidget::~MainWidget()
{

}
