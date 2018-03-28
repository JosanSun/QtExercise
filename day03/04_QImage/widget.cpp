#include <QPainter>


#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    QImage image(1118, 558, QImage::Format_ARGB32);
    QPainter p;
    p.begin(&image);

    p.drawImage(0, 0, QImage("../bk.png"));

    for(int i = 0; i < 50; ++i)
    {
        for(int j = 0; j < 50; ++j)
        {
            image.setPixel(QPoint(i, j), qRgb(0, 255, 0));
            //image.pixel(QPoint(i, j));
        }
    }

    p.end();

    image.save("../image.png");
}

Widget::~Widget()
{
    delete ui;
}
