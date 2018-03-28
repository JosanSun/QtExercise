#include <QBuffer>     // 内存文件
#include <QDebug>
#include <QDataStream>

#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    QByteArray arr;
    QBuffer memFile(&arr);
    memFile.open(QIODevice::WriteOnly);

    memFile.write("1111111111111111");
    memFile.write("2222222222222222");

    memFile.close();

    qDebug() << memFile.buffer();
    qDebug() << "array " << arr;

    QBuffer memFile1;
    memFile1.open(QIODevice::WriteOnly);
    QDataStream stream(&memFile1);
    stream << tr("测试") << 250;
    memFile1.close();
    qDebug() << memFile1.buffer();
    qDebug() << "----------------";
    qDebug() << QString(memFile1.buffer()).toUtf8().data();     // 整合在一起，无法读取。

    memFile1.open(QIODevice::ReadOnly);
    QDataStream in;
    in.setDevice(&memFile1);
    QString str;
    int a;
    in >> str >> a;
    memFile1.close();

    qDebug() << str.toUtf8().data() << a;
}

Widget::~Widget()
{
    delete ui;
}
