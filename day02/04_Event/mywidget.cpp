#include "mywidget.h"
#include "ui_mywidget.h"
#include <QDebug>
#include <QCloseEvent>
#include <QMessageBox>
#include <QEvent>

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);

    //启动定时器 单位是毫秒
    timerId = this->startTimer(1000);
    timerId2=this->startTimer(500);

    connect(ui->pushButton, &MyButton::clicked,
            [](){
        qDebug()<<QString::fromLocal8Bit("按钮被按下");
    });

    //安装过滤器
    ui->label_2->installEventFilter(this);
    ui->label_2->setMouseTracking(true);
}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::keyPressEvent(QKeyEvent *ev){
    qDebug()<<(char)ev->key();
    if(ev->key() == Qt::Key_0){
        qDebug()<<"Qt::Key_A";
    }
}

void MyWidget::timerEvent(QTimerEvent *ev){
    if(ev->timerId() == timerId){
        static int sec = 0;
        ui->label->setText(QString("<center><h1>Timer Out: %1"
                                   "</h1></center>").arg(sec++));
        if(5 == sec){
            killTimer(timerId);
        }
    }
    else if(ev->timerId() == timerId2){
        static int sec = 0;
        ui->label_2->setText(QString("<center><h1>Timer Out: %1"
                                   "</h1></center>").arg(sec++));
    }
}

void MyWidget::mousePressEvent(QMouseEvent *ev)
{
    qDebug()<<"+++++++++++";
}

void MyWidget::closeEvent(QCloseEvent *ev){
   int ret = QMessageBox::question(this, "question",
                         QString::fromLocal8Bit("是否需要关闭窗口"));
   if(ret == QMessageBox::Yes){
       //关闭窗口
       //处理关闭窗口事件，接收事件，事件就不会再往下传递；
       ev->accept();
   }
   else{
       //不关闭窗口
       //忽略事件，事件继续给父组件传递
       ev->ignore();
   }
}

bool MyWidget::event(QEvent *ev){
//    //事件分发
//    switch (ev->type()) {
//    case QEvent::Close:
//        closeEvent(ev);
//        break;
//    case QEvent::MouseMove:
//        mouseMoveEvent(ev);
//        break;
//        /*...*/
//    default:
//        break;
//    }

    if(ev->type() == QEvent::Timer){

//        //必须进行类型转换，否则报错
//        QTimerEvent *env = reinterpret_cast<QTimerEvent*>(ev);
//        timerEvent(env);

        //干掉定时器
        //如果返回true, 事件停止传播
        return true;
    }
    else if(ev->type() == QEvent::KeyPress){
        //类型转换
        QKeyEvent* env = reinterpret_cast<QKeyEvent*>(ev);
        if(env->key() == Qt::Key_B){
            return QWidget::event(ev);
        }
        return true;
    }
    else{
        //其他事件继续传播
        return QWidget::event(ev);

        //return false;   //这个可以让许多事件无效
    }
}

bool MyWidget::eventFilter(QObject *obj, QEvent *ev){
     if(obj == ui->label_2){
         QMouseEvent* env = reinterpret_cast<QMouseEvent *>(ev);

         if(ev->type() == QEvent::MouseMove){
             ui->label_2->setText(
                         QString("Mouse move:(%1, %2)").arg(env->x()).arg(env->y()));
            return true;
         }
         else if(ev->type() == QEvent::MouseMove){
             ui->label_2->setText(
                         QString("Mouse press:(%1, %2)").arg(env->x()).arg(env->y()));
            return true;
         }
         else{
            ui->label_2->setText(
                         QString("Mouse release:(%1, %2)").arg(env->x()).arg(env->y()));
            return true;
         }
     }
     else{
         return QWidget::eventFilter(obj, ev);
     }
}

