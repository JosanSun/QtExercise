#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QTimer>
#include "mythread.h"  //线程头文件

namespace Ui {
class MyWidget;
}

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = 0);
    ~MyWidget();



private slots:
    void on_pushButton_clicked();

    void dealTimeout();  //定时器槽函数
    void dealDone();  //处理线程槽函数
    void stopThread();   //结束线程

private:
    Ui::MyWidget *ui;

    QTimer* myTimer;
    MyThread* thread;
};

#endif // MYWIDGET_H
