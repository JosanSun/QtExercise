#include <QPainter>

#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 绘图设备， 400*300
    QPixmap pixmap(400, 300);

    QPainter p(&pixmap);

    // 填充白色背景色
    //p.fillRect(0, 0, 400, 300, QBrush(Qt::white));
    pixmap.fill(Qt::red);

    p.drawPixmap(0, 0, 200, 150, QPixmap("../bk.jpg"));

    // 保存图片
    pixmap.save("../pixmap.png");
}

Widget::~Widget()
{
    delete ui;
}
