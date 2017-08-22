#include "mybutton.h"
#include <QDebug>

MyButton::MyButton(QWidget *parent) : QPushButton(parent)
{

}

MyButton::~MyButton(){
    qDebug()<<QString::fromLocal8Bit("我被析构了");
}
