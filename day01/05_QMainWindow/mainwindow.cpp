#include "mainwindow.h"
#include <QDebug>
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QPushButton>
#include <QStatusBar>
#include <QLabel>
#include <QTextEdit>
#include <QDockWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //菜单栏
    //----------------------
    //menuBar()  就相当于 new QMenuBar(0);
    QMenuBar *mBar = menuBar();
    //添加菜单
    QMenu *pFile = mBar->addMenu(QString::fromLocal8Bit("文件"));
    //添加菜单项，  --添加动作
    QAction *pNew = pFile->addAction(QString::fromLocal8Bit("新建"));
    connect(pNew, &QAction::triggered,
            [=](){
        qDebug()<<QString::fromLocal8Bit("新建被按下");
    });
    pFile->addSeparator();
    QAction *pOpen = pFile->addAction(QString::fromLocal8Bit("打开"));

    //工具栏,菜单栏的快捷方式
    QToolBar* toolBar = addToolBar("toolBar");

    //工具栏添加快捷键
    toolBar->addAction(pNew);   //只需要QAction的指针

    QPushButton* b = new QPushButton(this);

    b->setText("^_^");
    toolBar->addWidget(b);

    connect(b, &QPushButton::pressed,
            [=](){
        b->setText("123");
    });

    //状态栏
    QStatusBar* qSta  = statusBar();
    QLabel *lab = new QLabel(this);
    lab->setText("Normal text file");
    qSta->addWidget(lab);
    //从左往右添加
    qSta->addWidget(new QLabel("2", this));   //Note:QLabel的构造函数

    //从右往左添加
    qSta->addPermanentWidget(new QLabel("123", this));

    //核心控件
    QTextEdit* text =  new QTextEdit(this);
    setCentralWidget(text);

    //浮动窗口
    QDockWidget* dock = new QDockWidget(this);
    //第一个参数是枚举值，第二个参数指针
    addDockWidget(Qt::RightDockWidgetArea, dock);
    QTextEdit* text1 =  new QTextEdit(this);

    dock->setWidget(text1);
    move(300, 200);
    resize(400, 400);
}

MainWindow::~MainWindow()
{

}
