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
    connect(&sub, SIGNAL(mySignal()), this, SLOT(changeWindow2()));
    connect(&sub, SIGNAL(mySignal(int,QString)), this,
                    SLOT(dealSlot(int,QString)));

    //Lambda表达式， 匿名函数对象
    //C++11增加的新特性，   项目文件CONFIG +=C++11
    //Qt配合信号一起使用，非常方便
    QPushButton *b4 = new QPushButton(this);
    b4->setText(QString::fromLocal8Bit("Lambda表达式"));
    b4->move(150, 150);
    connect(b4, &QPushButton::released,
            []()
    {
        qDebug()<<"11111111";
    });

    int a1 =10, b1 = 100;
    connect(b4, &QPushButton::released,
            // = :把外部所有局部变量、类中所有成员以值传递方式
            [=]()
    {
        b4->setText("lambda");
        qDebug()<<a1<<" "<<b1;

        //a1 = 50;
    });

    int a2 =10, b2 = 100;
    connect(b4, &QPushButton::clicked,
            // = :把外部所有局部变量、类中所有成员以值传递方式
            // this :
            // & :引用   当存在按钮这样的动态分配空间的按钮，尽量不要用引用

            //isCheck信号传参数
            [=](bool isCheck) mutable
    {

        qDebug()<<isCheck;

        a1 = 50;
        qDebug()<<a1<<" "<<b1;
    });

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
