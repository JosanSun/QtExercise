#include <QPainter>
#include <QPixmap>
#include <QMouseEvent>

#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 去窗口边框
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());

    // 把窗口设置为透明
    setAttribute(Qt::WA_TranslucentBackground);

    //setWindowFlags(Qt::Dialog);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *ev)
{
    QPainter p(this);
    p.drawPixmap(0, 0, QPixmap("../bk.png"));

}

void Widget::mousePressEvent(QMouseEvent *ev)
{
    if(Qt::RightButton == ev->button())
    {
        close();
    }
    else if(Qt::LeftButton == ev->button())
    {
        p  =ev->globalPos() - this->frameGeometry().topLeft();
    }
}

void Widget::mouseMoveEvent(QMouseEvent *ev)
{
    if(ev->buttons() & Qt::LeftButton)
    {
        // 注意ev->globalPos() 与mousePressEvent的坐标不一定相同
        move(ev->globalPos() - p);
    }
}

