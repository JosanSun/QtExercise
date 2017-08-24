#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QCompleter>
#include <QStringList>
#include <QMovie>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //这个是在ui上面进行设置得到的
    ui->setupUi(this);
    //注意button是个指针
    //ui->button->setText("123");

    QString str = ui->lineEdit->text();
    qDebug()<<str;
    ui->lineEdit->setText(
                QString::fromLocal8Bit("我爱你"));
    //void QLineEdit::setTextMargins(int left, int top, int right, int bottom)
    ui->lineEdit->setTextMargins(5, 0, 0, 0);
    //设置内容显示方式
    //ui->lineEdit->setEchoMode(QLineEdit::Password);

    //显示提示内容
    QStringList list;
    list<<"hello"<<"how  are you"<<" hehe";
    QCompleter *com = new QCompleter(list, this);
    com->setCaseSensitivity(Qt::CaseInsensitive);
    ui->lineEdit->setCompleter(com);

    //QLabel
    ui->labelText->setText("^_^");
    //设置图片
    ui->labelPic->setPixmap(QPixmap("://rsc/cool.png"));
    //让图片自动适应label大小
    ui->labelPic->setScaledContents(true);

    //创建动画对象
    QMovie* myMovie = new QMovie("://rsc/tuzi.gif");
    //设置动画
    ui->labelGif->setMovie(myMovie);
    //启动动画
    myMovie->start();
    //自适应大小
    ui->labelGif->setScaledContents(true);

    //设置网址
    ui->labelPage->setText(QString::fromLocal8Bit("<h1>"
                           "<a href=\"https://www.baidu.com\">百度一下</a></h1>"));
    //打开外部链接
    ui->labelPage->setOpenExternalLinks(true);

    //数码管
    ui->lcdNumber->display(123);   //设置内容

    //进度条
    ui->progressBar->setMinimum(0);   //设定最小值
    ui->progressBar->setMaximum(200); //设定最大值
    ui->progressBar->setValue(80);    //设定当前值
}


MainWindow::~MainWindow()
{
    delete ui;
}

//这样比 connect方便多了
void MainWindow::on_pushButton_3_clicked()
{
    static int i=0;
    ui->stackedWidget->setCurrentIndex(++i%4);
}
