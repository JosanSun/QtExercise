#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QDebug>
#include <QDate>
#define qcout qDebug() << "[" << __FILE__ << ":" << __LINE__ << "]"

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

void Widget::on_pushButtonRead_clicked()
{
    QString path = QFileDialog::getOpenFileName(this,
                         "open", "../", "TXT (*.txt)");
    if(!path.isEmpty())
    {
        QFile file(path);
        bool isOK = file.open(QIODevice::ReadOnly);
        if(true == isOK)
        {
#if 1
            // 读文件，默认只识别utf8编码
            QByteArray arr = file.readAll();
            ui->textEdit->setText(QString(arr));
            ui->textEdit->setText(arr);

#else
            QByteArray arr;
            while(!file.atEnd())
            {
                arr += file.readLine();
            }
            ui->textEdit->setText(arr);
#endif
        }

        file.close();

        // 获取文件信息
        QFileInfo info(path);
        qcout << "文件名字： " << info.fileName();
        qcout << "文件后缀： " << info.suffix();
        qcout << "文件大小： " << info.size();
        // 2016-01-04 15:13
        qcout << "文件创建时间： " << info.created().
                 toString("yyyy-MM-dd hh:mm:ss");
    }


}

void Widget::on_pushButtonWrite_clicked()
{

    QString path = QFileDialog::getSaveFileName(this, "save",
                                 "../", "TXT(*.txt)");
    if(!path.isEmpty())
    {
        QFile file;
        file.setFileName(path);

        bool isOK = file.open(QIODevice::WriteOnly);
        if(isOK)
        {
            QString str = ui->textEdit->toPlainText();

            //file.write(str.toUtf8());

            file.write(str.toStdString().data());

            //QString -> QByteArray
            QString buf = "123";
            QByteArray a = buf.toUtf8();
            a = buf.toLocal8Bit();

            //QByteArray -> char*
            char* b = a.data();

            //char* -> QString
            char* p = "abc";
            QString c = QString(p);
        }

        file.close();
    }
}
