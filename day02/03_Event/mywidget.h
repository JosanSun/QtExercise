#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
class QKeyEvent;
class QTimerEvent;
class QCloseEvent;
class QMouseEvent;
class QEvent;

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
    void keyPressEvent(QKeyEvent* ev);
    //void timerEvent(QTimerEvent* ev);
    void mousePressEvent(QMouseEvent* ev);
    void closeEvent(QCloseEvent* ev);
    bool event(QEvent *ev);
    void paintEvent(QPaintEvent* ev);

    //bool eventFilter(QObject *watched, QEvent *ev);

private:
    Ui::MyWidget *ui;

    //int timerId;
    //int timerId2;
};

#endif // MYWIDGET_H
