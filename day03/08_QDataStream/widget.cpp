#include <QFile>
#include <QDataStream>
#include <QDebug>

#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    writeData();

    readData();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::writeData()
{
    QFile file("../test.txt");

    bool isOk  = file.open(QIODevice::WriteOnly);
    if(isOk)
    {
        QDataStream ostream(&file);

        ostream << QString(tr("主要看气质")) << 250;

        file.close();
    }
}

void Widget::readData()
{
    QFile file("../test.txt");

    bool isOk = file.open(QIODevice::ReadOnly);
    if(isOk)
    {
        QDataStream istream(&file);

        QString str;
        int a;

        istream >> str >> a;
        qDebug() << str << a;
    }
}





