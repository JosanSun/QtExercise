#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QMenuBar* mBar = menuBar();
    QMenu* menu = mBar->addMenu(tr("对话框"));
    QAction* p1 = menu->addAction(tr("模态对话框"));
    QAction* p2 = menu->addAction(tr("非模块对话框"));

    connect(p1, &QAction::triggered,
            [this]()
            {
               QDialog dlg;
               dlg.exec();
               qDebug() << "这是模块对话框";
            });
    connect(p2, &QAction::triggered,
            [this]()
            {
                QDialog* dlg = new QDialog;
                dlg->setAttribute(Qt::WA_DeleteOnClose);
                dlg->show();

                qDebug() << "这是非模态对话框";
            });

    QMenu* messageBox = mBar->addMenu(tr("消息框"));
    QAction* p3 = messageBox->addAction(tr("关于对话框"));
    connect(p3, &QAction::triggered,
            [=]()
            {
                QMessageBox::about(this, tr("这是关于对话框"),
                                             tr("这只是一个测试"));
            });
    QAction* p4 = messageBox->addAction(tr("问题对话框01"));
    connect(p4, &QAction::triggered,
            [=]()
            {
                int ret = QMessageBox::question(this, tr("这是问题对话框"),
                                                tr("这是问题对话框的第一个测试"));
                switch(ret)
                {
                case QMessageBox::Yes:
                    qDebug() << "Yes is pressed";
                    break;
                case QMessageBox::No:
                    qDebug() << "No is pressed";
                    break;
                default:
                    break;
                }
            });
    QAction* p5 = messageBox->addAction(tr("问题对话框02"));
    connect(p5, &QAction::triggered,
            [=]()
            {
                int ret = QMessageBox::question(this, tr("这是另外一个问题对话框"),
                                                tr("这是问题对话框的第二个测试"),
                                                QMessageBox::Ok | QMessageBox::No |
                                                QMessageBox::Cancel | QMessageBox::Close);
                qDebug() << "The value of ret is " << ret;
            });

    QMenu* fileDialogMenu = menuBar()->addMenu(tr("文件对话框菜单"));
    QAction* fileDialogAction = fileDialogMenu->addAction(tr("文件对话框"));
    connect(fileDialogAction, &QAction::triggered,
            [=]()
            {
                QString path = QFileDialog::getOpenFileName(this, "open",
                                                            "D://",
                                                            "Images (*.png *.jpg);;"
                                                            "Text files (*.txt);;"
                                                            "source (*.cpp);;"
                                                            "all (*.*)");
                qDebug() << path;
            });

    resize(800, 600);
}

MainWindow::~MainWindow()
{

}
