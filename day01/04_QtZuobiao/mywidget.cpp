#include <QPushButton>

#include "mywidget.h"

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
{
    move(100, 100);
    QPushButton* b1 = new QPushButton(this);
    b1->move(50, 50);
    b1->setText("^_^");
    b1->resize(200, 200);

    QPushButton* b2 = new QPushButton(b1);
    b2->move(50, 50);
    b2->setText("@_@");
}

MyWidget::~MyWidget()
{

}
