#include <QLabel>
#include <QMovie>
#include <QDebug>
#include <QTime>
#include <QMovie>
#include <QTextEdit>
#include <QMessageBox>

#include "mywidget.h"
#include "ui_mywidget.h"

#define qcout (qDebug() << "[" << __FILE__ << ":" << __LINE__ << "]")

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);

    ui->stackedWidget->setCurrentWidget(ui->pageSet);

    overMovie.setFileName(":/images/lose.gif");
    ui->labelOver->setMovie(&overMovie);
    ui->labelOver->setScaledContents(true);

    winMovie.setFileName(":/images/win.gif");
    ui->labelWin->setMovie(&winMovie);
    ui->labelWin->setScaledContents(true);

    connect(ui->pushButton0_2, &QPushButton::clicked, this, &MyWidget::dealNum);
    connect(ui->pushButton1_2, &QPushButton::clicked, this, &MyWidget::dealNum);
    connect(ui->pushButton2_2, &QPushButton::clicked, this, &MyWidget::dealNum);
    connect(ui->pushButton3_2, &QPushButton::clicked, this, &MyWidget::dealNum);
    connect(ui->pushButton4_2, &QPushButton::clicked, this, &MyWidget::dealNum);
    connect(ui->pushButton5_2, &QPushButton::clicked, this, &MyWidget::dealNum);
    connect(ui->pushButton6_2, &QPushButton::clicked, this, &MyWidget::dealNum);
    connect(ui->pushButton7_2, &QPushButton::clicked, this, &MyWidget::dealNum);
    connect(ui->pushButton8_2, &QPushButton::clicked, this, &MyWidget::dealNum);
    connect(ui->pushButton9_2, &QPushButton::clicked, this, &MyWidget::dealNum);
}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::on_pushButtonStart_clicked()
{
    gameTime = ui->comboBox->currentText().toInt();
    qDebug() << gameTime << "s";

    ui->stackedWidget->setCurrentWidget(ui->pageGame);

    int num;
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

    while((num = qrand() % 10000) < 999);
    randStr = QString::number(num);
    qDebug() << "randNum = " << randStr;

    // 设置进度条
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(gameTime);
    ui->progressBar->setValue(gameTime);

    gameTimerId = 0;

    gameTimerId = startTimer(1000);

    resultStr.clear();
    ui->textEdit->clear();

}

void MyWidget::on_pushButtonEnd_clicked()
{
    close();
}

void MyWidget::timerEvent(QTimerEvent *ev)
{
    if(ev->timerId() == gameTimerId)
    {
        --gameTime;

        // 设置进度条
        ui->progressBar->setValue(gameTime);

        if(0 == gameTime)
        {
            killTimer(gameTimerId);

            QMessageBox::information(this, tr("失败"),
                                     tr("时间到了！！！"));
            overMovie.start();

            ui->stackedWidget->setCurrentWidget(ui->pageOver);

            overTimerId = startTimer(5000);
        }
    }
    else if(ev->timerId() == overTimerId)
    {
        overMovie.stop();
        killTimer(overTimerId);

        ui->stackedWidget->setCurrentWidget(ui->pageSet);
    }
    else if(ev->timerId() == winTimerId)
    {
        winMovie.stop();
        killTimer(winTimerId);

        ui->stackedWidget->setCurrentWidget(ui->pageSet);
    }
    else
    {
        QWidget::timerEvent(ev);
    }
}

void MyWidget::dealNum()
{
    QObject* mySender = sender();
     QPushButton* p = static_cast<QPushButton*>(mySender);

    if(p)
    {
        QString numStr = p->text();
        resultStr += numStr;

        if(1 == resultStr.size() && "0" == resultStr)
        {
            resultStr.clear();
        }

        if(resultStr.size() <= 4)
        {
            ui->textEdit->setText(resultStr);
        }

        if(4 == resultStr.size())
        {
            if(resultStr > randStr)
            {
                ui->textEdit->append(tr("数字大了！"));
            }
            else if(resultStr < randStr)
            {
                ui->textEdit->append(tr("数字小了！"));
            }
            else
            {
                ui->textEdit->append(tr("恭喜你！猜对了！"));

                killTimer(gameTimerId);

                winMovie.start();
                ui->stackedWidget->setCurrentWidget(ui->pageWin);

                winTimerId = startTimer(5000);
            }
            resultStr.clear();
        }

    }
}

void MyWidget::on_pushButtonDel_clicked()
{
    if(1 == resultStr.size())
    {
        resultStr.clear();
        ui->textEdit->clear();
    }
    else
    {
        resultStr.chop(1);
        // resultStr[resultStr.size() - 1] = '\0';
        ui->textEdit->setText(resultStr);
    }
}


void MyWidget::on_pushButtonEnter_clicked()
{
    resultStr.clear();
    QString str = "随机数为：" + randStr;
    ui->textEdit->setText(str);
}
