#include <QPainter>
#include <QPixmap>
#include <QBitmap>

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

void Widget::paintEvent(QPaintEvent * /* ev */)
{
    QPainter p(this);
    p.drawPixmap(0, 0, QPixmap("../bk.jpg"));
    p.drawPixmap(200, 0, QBitmap("../bk.jpg"));

    QPixmap pixmap;
    pixmap.load("../bk.jpg");
    p.drawPixmap(0, 200, pixmap);
}
