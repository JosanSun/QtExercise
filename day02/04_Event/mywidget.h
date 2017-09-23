#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>

namespace Ui {
class MyWidget;
}

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = 0);
    ~MyWidget();
protected:
    //键盘按下事件
    void keyPressEvent(QKeyEvent* ev);
    //计时器事件
    void timerEvent(QTimerEvent* ev);

    void mousePressEvent(QMouseEvent* ev);
    //关闭事件
    void closeEvent(QCloseEvent* ev);

    bool event(QEvent *ev);

    //事件过滤器
    bool eventFilter(QObject *obj, QEvent *ev);

private:
    Ui::MyWidget *ui;

    int timerId;
    int timerId2;
};

#endif // MYWIDGET_H
