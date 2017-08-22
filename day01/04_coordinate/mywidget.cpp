#include "mywidget.h"
#include "mybutton.h"

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
{
    //相对于屏幕
    move(100, 100);

    //对于QObject的对象，会自动释放空间
    MyButton * b1 = new MyButton(this);
    b1->setText("123");


}

MyWidget::~MyWidget()
{

}
