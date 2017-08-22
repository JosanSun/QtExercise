#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    b1.setParent(this);
    b1.setText("close");
    b1.move(100, 100);

    b2 = new QPushButton(this);
    b2->setText("123");

    //b1信号发出者， b2信号接收者
    //signal slot
    connect(&b1, &QPushButton::pressed, this, &MainWidget::close);


    //一个自定义的槽函数
    connect(b2, &QPushButton::released, this, &MainWidget::mySlot);

    //b2发一个信号，两个slot来接收
    connect(b2, &QPushButton::released, &b1, &QPushButton::hide);
}

void MainWidget::mySlot(){
    b2->setText("abc");
}

MainWidget::~MainWidget()
{

}
