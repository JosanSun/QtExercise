#include <QDebug>
#include <QMenuBar>
#include <QMenu>
#include <QStatusBar>
#include <QLabel>
#include <QTextEdit>
#include <QDockWidget>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    // 菜单栏
    // 创建菜单栏，方法一
    //QMenuBar* mBar = new QMenuBar(this);
    //setMenuBar(mBar);
    // 创建菜单栏，方法二 常用
    QMenuBar* mBar = menuBar();

    QMenu* fileMenu = mBar->addMenu(tr("文件"));
    QAction* newAction = fileMenu->addAction(tr("新建"));
    fileMenu->addSeparator();
    QAction* saveAction = fileMenu->addAction(tr("保存"));

    QMenu* editMenu = mBar->addMenu(tr("编辑"));
    QAction* copyAction = editMenu->addAction(tr("复制"));
    QAction* pasteAction = editMenu->addAction(tr("粘贴"));

    // 核心控件栏
    QTextEdit* textEdit = new QTextEdit(this);
    this->setCentralWidget(textEdit);

    // 状态栏
    QStatusBar* statBar = this->statusBar();
    setStatusBar(statBar);
    QLabel* label1 = new QLabel(this);
    label1->setText(tr("这是状态栏"));
    statBar->addWidget(label1);
    QLabel* label2 = new QLabel(this);
    label2->setText(tr("这是状态栏的后面"));
    statBar->addPermanentWidget(label2);

    // 浮动窗口
    QDockWidget* dockWidget = new QDockWidget(this);
    this->addDockWidget(Qt::RightDockWidgetArea, dockWidget);
    // 在浮动窗口里面加一个文本编辑框
    QTextEdit* textEdit1 = new QTextEdit(this);
    dockWidget->setWidget(textEdit1);

    resize(500, 300);
}

MainWindow::~MainWindow()
{

}
