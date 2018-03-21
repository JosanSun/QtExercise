#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>

// class QMovie;        // fail to run
#include <QMovie>

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
    void on_pushButtonStart_clicked();
    void on_pushButtonEnd_clicked();
    void dealNum();

    void on_pushButtonDel_clicked();

    void on_pushButtonEnter_clicked();

protected:
    void timerEvent(QTimerEvent *ev);

private:

    Ui::MyWidget *ui;

    QString randStr;
    QString resultStr;
    int gameTime;
    int gameTimerId;
    int overTimerId;
    int winTimerId;

    // 指针可以使用提前声明，对于变量则必须包括头文件
    QMovie overMovie;
    QMovie winMovie;
};

#endif // MYWIDGET_H
