#include "subwidget.h"

SubWidget::SubWidget(QWidget *parent) : QWidget(parent)
{
    setWindowTitle(QString::fromLocal8Bit("小弟"));
    b.setText(QString::fromLocal8Bit("切换到主窗口"));
    b.setParent(this);

    connect(&b, &QPushButton::pressed, this, &SubWidget::myAction);

    resize(300, 400);
}

void SubWidget::myAction(){
    emit mySignal();
    //不能这样写，需要写入参数
    //emit mySignal(int , QString);
    emit mySignal(120, QString::fromLocal8Bit("我是子窗口"));
}
