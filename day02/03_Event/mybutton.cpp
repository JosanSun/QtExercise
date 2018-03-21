#include <QMouseEvent>
#include <QDebug>
#include <QPushButton>

#include "mybutton.h"

MyButton::MyButton(QWidget *parent) : QPushButton(parent)
{

}

void MyButton::mousePressEvent(QMouseEvent *ev)
{
    if(Qt::LeftButton == ev->button())
    {
        qDebug() << QString(tr("按下了左键"));
    }
}
