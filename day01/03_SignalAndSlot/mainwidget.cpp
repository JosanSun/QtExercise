#include <QDebug>

#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    this->setWindowTitle(tr("主界面"));
    mainButton = new QPushButton(this);
    mainButton->setText(tr("主按钮，切换到次界面"));
    mainButton->move(50, 25);

    subWidget.setWindowTitle(tr("次界面"));
    subButton = new QPushButton(&subWidget);
    subButton->setText(tr("次按钮，切换到主界面"));
    subButton->move(50, 50);
    //subButton->hide();

    subWidget1 = new SubWidget;

    connect(mainButton, &QPushButton::clicked,
            this, &MainWidget::showSubWidget);
    connect(subButton, &QPushButton::clicked,
            this, &MainWidget::showMainWidget);

    void (SubWidget::*pfnChangeSlot)() = SubWidget::changeSlot;
    void (SubWidget::*pfnChangeSlot1)(int, QString) = SubWidget::changeSlot;

    connect(subWidget1, pfnChangeSlot,
            this, &MainWidget::showMainWidget1);
    connect(subWidget1, pfnChangeSlot1,
            this, &MainWidget::printText);

    // 注意如果是局部变量   QPushButton lambdaButton;
    // 这个在构造函数运行结束完毕之后，会自动释放，所以看不见这个按钮
    QPushButton* lambdaButton = new QPushButton;
    lambdaButton->setText("This is lambda test");
    lambdaButton->setParent(this);
    lambdaButton->setCheckable(true);
    int aInt = 100;
    double aDouble = 120.00;
    connect(lambdaButton, &QPushButton::clicked,
            [=](bool isCheck) mutable
            {
                if(isCheck)
                {
                    qDebug() << "isCheck is true";
                }
                else
                {
                    qDebug() << "isCheck is false";
                }

                qDebug() << "aInt is " << aInt;
                qDebug() << "aDouble is " << aDouble;
            }
            );

    QPushButton testButton;
    testButton.setText("This is a local variable button test");
    testButton.setParent(this);
    testButton.move(100, 100);
    testButton.show();
    // 无法显示，因为真正可以显示的时候是在主窗口显示的时候，即w.show();
    // 而w.show()调用的时候，w的构造函数已经执行完毕，也就是说testButton已经被释放。
}

MainWidget::~MainWidget()
{

}

void MainWidget::showSubWidget()
{
    subWidget.show();
    subWidget1->show();
    this->hide();
}

void MainWidget::showMainWidget()
{
    subWidget.hide();
    this->show();
}

void MainWidget::showMainWidget1()
{
    subWidget1->hide();
    this->show();
}

void MainWidget::printText(int a, QString text)
{
    qDebug() << a << "  " << text;
}
