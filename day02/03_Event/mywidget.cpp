#include <QDebug>
#include <QCloseEvent>
#include <QEvent>
#include <QMouseEvent>
#include <QMessageBox>
#include <QTimerEvent>
#include <QKeyEvent>
#include <QLabel>

#include "mywidget.h"
#include "ui_mywidget.h"

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);

    //timerId = this->startTimer(1000);
    //timerId2 = this->startTimer(500);

    connect(ui->pushButton, &MyButton::clicked,
            []()
            {
                qDebug() << tr("按钮被按下");
            });



    //ui->label_2->installEventFilter(this);
    ui->label_2->setMouseTracking(true);
    move(1000, 50);
}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::keyPressEvent(QKeyEvent *ev)
{
    qDebug() << ev->key();
    if(Qt::Key_0 == ev->key())
    {
        qDebug() << "Qt::Key_A";
    }
}

void MyWidget::paintEvent(QPaintEvent *ev)
{
    qDebug() << "Paint is called";
    QWidget::paintEvent(ev);
}

//void MyWidget::timerEvent(QTimerEvent *ev)
//{
//    if(timerId == ev->timerId())
//    {
//        static int sec = 0;
//        ui->label->setText(tr("<center><h1>Timer Out: %1"
//                              "</h1></center>").arg(sec++));
//        if(5 == sec)
//        {
//            killTimer(timerId);
//        }
//    }
//    else if(timerId2 == ev->timerId())
//    {
//        static int sec = 0;
//        ui->label_2->setText(tr("<center><h1>Timer Out: %1"
//                                "</h1></center>").arg(sec++));
//    }
//}

void MyWidget::mousePressEvent(QMouseEvent* /* ev */)
{
    qDebug() << "+++++++++++++++++++";
}

void MyWidget::closeEvent(QCloseEvent *ev)
{
    int ret = QMessageBox::question(this, tr("question"),
                                    tr("是否需要关闭窗口"));
    if(QMessageBox::Yes == ret)
    {
        ev->accept();
    }
    else
    {
        ev->ignore();
    }
}

bool MyWidget::event(QEvent *ev)
{
    return true;
    if(QEvent::Timer == ev->type())
    {
        QTimerEvent* env = static_cast<QTimerEvent*>(ev);
        timerEvent(env);
        return true;
    }
    else if(QEvent::KeyPress == ev->type())
    {
        QKeyEvent* env = static_cast<QKeyEvent*>(ev);
        if(Qt::Key_B == env->key())
        {
            return QWidget::event(ev);
        }
        return true;
    }
    else
    {
        static int i = 0;
        qDebug() << i++ << ": MyWidget::event()" ;
        return QWidget::event(ev);
    }
}

//bool MyWidget::eventFilter(QObject *watched, QEvent *ev)
//{
//    if(watched == ui->label_2)
//    {
//        QMouseEvent* env = static_cast<QMouseEvent*>(ev);

//        if(QEvent::MouseMove == ev->type())
//        {
//            ui->label_2->setText(tr("Mouse move:(%1, %2)").arg(env->x())
//                                 .arg(env->y()));
//            return true;
//        }
//        else if(QEvent::MouseButtonPress == ev->type())
//        {
//            ui->label_2->setText(tr("Mouse press:(%1, %2)").arg(env->x())
//                                 .arg(env->y()));
//            return true;
//        }
//        else
//        {
//            ui->label_2->setText(tr("Mouse release:(%1, %2)")
//                                 .arg(env->x())
//                                 .arg(env->y()));
//            return true;
//        }
//    }
//    else
//    {
//        return QWidget::eventFilter(watched, ev);
//    }
//}

