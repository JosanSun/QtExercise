#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //给整个Widget里面的label设置格式
    this->setStyleSheet("QLabel{color:rgb(0, 0, 255);"
                             "background-color:red;"
                            "border-image:url(:/new/rsc/ren.jpg);"
                             "}");
    //给单独label进行微调
    ui->label->setStyleSheet("QLabel{color:rgb(0, 255, 255);"
                             "background-color: green;"
                             "background-image:url(:/new/rsc/ren.jpg)"
                             "}");
}

Widget::~Widget()
{
    delete ui;
}
