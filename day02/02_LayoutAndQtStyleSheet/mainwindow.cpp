#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setStyleSheet("QLabel{"
                        "color:rgb(0, 255, 255);"
                        "background-color: white;"
                        "font: bold;"
                        "}");

    // 平铺图片，无法达到可伸缩
    ui->labelMy->setStyleSheet("QLabel{"
                             "color:red;"
                             "background-color: white;"
                             "font: bold;"
                             "background-image:url(:/images/inter.gif);"
                             "}");

    // QLabel 和 QPushButton 都可以使用border-image
    ui->pushButtonTest->setStyleSheet("QPushButton{"
                               "color:red;"
                               "border-width: 4px;"
                               "border-image: url(:/images/tuzi.gif);"
                               "}");


    // 将图片往四个方向裁剪30像素
    ui->label_2->setStyleSheet("QLabel{"
                               "color:red;"
                               "border-width: 4px;"
                               "border-image: url(:/images/tuzi.gif) 30 30 30 30 stretch stretch;"
                               "}");

    this->resize(1000, 800);
}

MainWindow::~MainWindow()
{
    delete ui;
}
