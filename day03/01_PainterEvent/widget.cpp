#include <QPainter>
#include <QPen>
#include <QBrush>

#include "widget.h"
#include "ui_widget.h"

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
    //QPainter p(this);
    QPainter p;
    p.begin(this);

//    p.drawPixmap(0, 0, width(), height(),
//                 QPixmap("../bk.jpg"));

    p.drawPixmap(rect(), QPixmap("../bk.jpg"));

    // 定义画笔
    QPen pen;
    pen.setWidth(5);
    //pen.setColor(QColor::red);
    pen.setColor(QColor(14, 9, 234));
    pen.setStyle(Qt::DashLine);
    p.setPen(pen);     // 关联

    // 定义画刷
    QBrush brush;
    brush.setColor(Qt::red);
    brush.setStyle(Qt::Dense1Pattern);
    p.setBrush(brush);

    // 横线
    p.drawLine(50, 50, 150, 50);
    // 竖线
    p.drawLine(50, 50, 50, 150);

    // 矩形
    p.drawRect(150, 150, 100, 50);


    // 画圆形
    p.drawEllipse(200, 200, 50, 50);

    p.end();
}





