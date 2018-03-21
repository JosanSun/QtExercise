#include <QFile>
#include <QTextStream>   // 优点：可以指定编码格式
#include <QDebug>
#include <QFileDialog>

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
    if(file.open(QIODevice::WriteOnly))
    {
       QTextStream ostream(&file);
       ostream.setCodec("UTF-8");
       ostream << "主要看气质" << 250;

       file.close();
    }

}

void Widget::readData()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open"), "../");
    if(!path.isEmpty())
    {
        QFile file;
        file.setFileName(path);

        if(file.open(QIODevice::ReadOnly))
        {
            QTextStream istream(&file);

            //指定编码
            istream.setCodec("UTF-8");

            QString str;


            istream >> str ;

            qDebug() << str ;

            file.close();
        }
    }

}
