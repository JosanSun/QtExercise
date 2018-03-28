#include "mainwidget.h"
#include <QApplication>
#include <QDebug>


int main01(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWidget w;
    w.show();

    //qDebug() << 200 << "\n" << 400;

    QString q("Hello\nHelo");
    QStringList list1 = q.split('\n');


    qDebug() << "-------------------";

    for(QString str : list1)
    {
        qDebug() << str;
    }

    return a.exec();
}



