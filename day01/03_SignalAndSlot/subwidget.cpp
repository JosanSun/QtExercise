#include <QPushButton>

#include "subwidget.h"

SubWidget::SubWidget(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle(tr("这是次窗口，另外一个类"));

    subclassButton = new QPushButton(this);
    subclassButton->setText(tr("开始测试吧，切花到主窗口"));
    subclassButton->move(50, 50);

    QPushButton* button1 = new QPushButton(this);
    button1->setText(tr("打印字符串"));


    connect(subclassButton, &QPushButton::clicked,
            this, &SubWidget::emitChangeSlot);
    connect(button1, &QPushButton::clicked,
            this, &SubWidget::emitPrintSignal);
}

void SubWidget::emitChangeSlot()
{
    emit changeSlot();
}

void SubWidget::emitPrintSignal()
{
    //emit changeSlot(200, QString("这是什么？"));
    emit changeSlot(200, QString(tr("This is subwidget's signals.\n"
                                    "我是子窗口的信号")));
}


