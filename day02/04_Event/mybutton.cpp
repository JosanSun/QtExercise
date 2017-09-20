#include "mybutton.h"
#include <QMouseEvent>
#include <QDebug>

MyButton::MyButton(QWidget *parent) : QPushButton(parent)
{

}

void MyButton::mousePressEvent(QMouseEvent *e){
    if(e->button() == Qt::LeftButton){
        //如果是左键按下
        qDebug()<<QString::fromLocal8Bit("按下了左键");

        //事件接收后，就会往下传递
        //忽略，事件继续往下传递，给谁传递？
        //事件传递给了父组件，不是给父类（基类）
        //e->ignore();
    }
    else {
//        //信号的忽略
//        QPushButton::mousePressEvent(e);
    }
    //事件继续传递， 信号的再发送
    //QPushButton::mousePressEvent(e);
}
