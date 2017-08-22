#include "mainwindow.h"
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QMenuBar* mBar = menuBar();
    setMenuBar(mBar);
    QMenu* menu = mBar->addMenu(QString::fromLocal8Bit("对话框"));
    QAction* p1 = menu->addAction(QString::fromLocal8Bit("模态对话框"));
    QAction* p2 = menu->addAction(QString::fromLocal8Bit("非模态对话框"));

    //貌似对话框指不指定父对象，没什么区别
    //模态对话框
    connect(p1, &QAction::triggered,
            [this](){
        QDialog dlg(this);
        dlg.exec();
        qDebug()<<"This is 123";
    }
    );

    //非模态对话框
    connect(p2, &QAction::triggered,
            [=](){
        QDialog* dlg =  new QDialog(this);
        dlg->setAttribute(Qt::WA_DeleteOnClose);
        dlg->show();

        QDialog dlg1;
        dlg1.show();
        qDebug()<<"This is 111";
    }
    );


    QAction* p3 = menu->addAction(QString::fromLocal8Bit("关于对话框"));
    connect(p3, &QAction::triggered,
            [=](){
       QMessageBox::about(this, "title",
                          QString::fromLocal8Bit("关于QT"));
    }
    );

    QAction* p4 = menu->addAction(QString::fromLocal8Bit("问题对话框"));
    connect(p4, &QAction::triggered,
            [=](){
//        //使用默认按钮
//       int ret = QMessageBox::question(this, "question",
//                          QString::fromLocal8Bit("你还好吗？"));
//       switch(ret){
//       case QMessageBox::Yes:
//           qDebug()<<"i am OK";
//           break;
//       case QMessageBox::No:
//           qDebug()<<"i am bad";
//           break;
//       default:
//           break;
//       }

       //使用自定义按钮
      int ret = QMessageBox::question(this, "question",
                         QString::fromLocal8Bit("你还好吗？"),
                                       QMessageBox::Ok|
                                       QMessageBox::No|
                                       QMessageBox::Cancel|
                                       QMessageBox::Open);
      switch(ret){
      case QMessageBox::Ok:
          qDebug()<<"i am OK";
          break;
      case QMessageBox::No:
          qDebug()<<"i am No";
          break;
      case QMessageBox::Cancel:
          qDebug()<<"i am Cancel";
          break;
      case QMessageBox::Open:
          qDebug()<<"i am Open";
          break;
      default:
          break;
      }
    }
    );

    QAction* p5 = menu->addAction(QString::fromLocal8Bit("文件对话框"));
    connect(p5, &QAction::triggered,
            [=](){
       QString path = QFileDialog::getOpenFileName(this, "open",
                          "../", "Images (*.png "
                                 "*.xpm *.jpg);;Text files (*.txt);;XML "
                                 "files (*.xml);;all(*.*)");
        qDebug()<<path;
    }
    );

}


MainWindow::~MainWindow()
{

}
