#include <QStringList>
#include <QCompleter>
#include <QLineEdit>

#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->centralWidget;
    //ui->mainToolBar;
    ui->menuBar;
    this->ui->centralWidget;

    myWnd = new MyWindow;
    myWnd->show();

    setWindowTitle(tr("UI 窗口"));

    // 提示输出
    QStringList list;
    list << "Josan Sun" << "josan" << "josancpp";
    QCompleter* com = new QCompleter(list, this);
    com->setCaseSensitivity(Qt::CaseInsensitive);
    ui->lineEditName->setCompleter(com);


    ui->lineEditCode->setEchoMode(QLineEdit::Password);
}

MainWindow::~MainWindow()
{
    delete ui;
}
