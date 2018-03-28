#include <QLabel>
#include <QMouseEvent>
#include <QMouseEvent>
#include <QDebug>

#include "mylabel.h"

MyLabel::MyLabel(QWidget *parent) : QLabel(parent)
{

}

void MyLabel::mousePressEvent(QMouseEvent *ev)
{
    int i = ev->x();
    int j = ev->y();

    if(Qt::LeftButton == ev->button())
    {
        qDebug() << "Left";
    }
    else if(Qt::RightButton == ev->button())
    {
        qDebug() << "Right";
    }
    else if(Qt::MidButton == ev->button())
    {
        qDebug() << "Middle";
    }
    else
    {
        qDebug() << "Other";
    }

    QString text = QString("<center><h1>Mouse Press: (%1, %2)"
                           "</h1></center>").arg(i).arg(j);
    this->setText(text);
    //QWidget::mousePressEvent(ev);   // 继续传播事件
    //ev->ignore();                   // 继续传播事件
    //ev->accept();                   // 停止事件传播
}

void MyLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    int i = ev->x();
    int j = ev->y();
    QString text = QString("<center><h1>Mouse Release: (%1, %2)"
                           "</h1></center>").arg(i).arg(j);
    this->setText(text);
}

void MyLabel::mouseMoveEvent(QMouseEvent *ev)
{
    int i = ev->x();
    int j = ev->y();
    QString text = QString("<center><h1>Mouse Move: (%1, %2)"
                           "</h1></center>").arg(i).arg(j);
    this->setText(text);
}

void MyLabel::enterEvent(QEvent*  ev )
{
    QString text = QString("<center><h1>Mouse Enter"
                           "</h1></center>");
    this->setText(text);
}

void MyLabel::leaveEvent(QEvent* /* ev */)
{
    QString text = QString("<center><h1>Mouse Leave"
                           "</h1></center>");
    this->setText(text);
}

bool MyLabel::event(QEvent *ev)
{
    static int i = 0;
    qDebug() << i++ << ": MyLabel::event()" ;
    return QWidget::event(ev);
}
