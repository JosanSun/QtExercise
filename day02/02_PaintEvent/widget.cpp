#include "widget.h"
#include "ui_widget.h"
#include <QPainter>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *ev)
{
    //创建画家对象
    //方法一：
    //QPainter p(this);
    //方法二：
    QPainter p;
    p.begin(this);

    //绘图操作

    p.end();
}
