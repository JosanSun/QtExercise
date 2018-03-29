#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    myTimer = new QTimer(this);

    connect(myTimer, &QTimer::timeout,
            [=]()
            {
               static int sec = 0;
               if(0 == ui->lcdNumber->intValue())
               {
                   sec = 0;
               }
               ui->lcdNumber->display(++sec);


            });

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_buttonStart_clicked()
{
    myTimer->start(100);
}

void Widget::on_buttonStop_clicked()
{
    myTimer->stop();

    // add
    ui->lcdNumber->display(0);
}
