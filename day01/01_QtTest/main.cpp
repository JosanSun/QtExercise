#include "mywidget.h"
#include <QApplication>
#include <QDebug>
#include <QTextCodec>
#include <vector>
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    int n=10;
    vector<int>  ivec(n);
    for(int i=0;i<n;++i){
        ivec[i] = i+1;
    }

    for(int i = 0;i<<n;++i){
        cout<<ivec[i]<<"  ";
    }
//    //QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GB2312"));
//    QApplication a(argc, argv);
//    MyWidget w;
//    w.show();




//    //test1
//    QString str;
//    str = str.fromLocal8Bit("哈哈哈");

//    qDebug()<<QString::fromLocal8Bit("我爱你");
//    //test2
//    QTextCodec *codec = QTextCodec::codecForLocale();
//    QString astr = codec->toUnicode("安师大手动");

//    qDebug()<<str;
//        qDebug()<<astr;

//    return a.exec();
    return 0;
}
