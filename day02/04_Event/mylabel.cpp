#include "mylabel.h"
#include <QMouseEvent>
#include <QDebug>

MyLabel::MyLabel(QWidget *parent) : QLabel(parent)
{

}

void MyLabel::mousePressEvent(QMouseEvent *ev){
    int i = ev->x();
    int j = ev->y();
    //sprintf

    if(ev->button() == Qt::LeftButton){
        //...
        qDebug()<<"left";

    }
    else if(ev->button() == Qt::RightButton){
        //...
         qDebug()<<"right";
    }
    else if (ev->button() == Qt::MidButton){
        //...
         qDebug()<<"middle";
    }
    else {
        //...
         qDebug()<<"other";
    }


    QString text = QString("<center><h1>Mouse Press: (%1, %2)"
                           "</h1></center>").arg(i).arg(j);
    this->setText(text);
}

void MyLabel::mouseReleaseEvent(QMouseEvent *ev){
    int i = ev->x();
    int j = ev->y();
    QString text = QString("<center><h1>Mouse Release: (%1, %2)"
                           "</h1></center>").arg(i).arg(j);
    this->setText(text);
}

void MyLabel::mouseMoveEvent(QMouseEvent *ev){
    int i = ev->x();
    int j = ev->y();
    QString text = QString("<center><h1>Mouse Move: (%1, %2)"
                           "</h1></center>").arg(i).arg(j);
    //this->setText(text);
}

void MyLabel::enterEvent(QEvent *ev){
    QString text = QString("<center><h1>Mouse Enter"
                           "</h1></center>");
    this->setText(text);
}

void MyLabel::leaveEvent(QEvent *ev){
    QString text = QString("<center><h1>Mouse Leave"
                           "</h1></center>");
    this->setText(text);
}
