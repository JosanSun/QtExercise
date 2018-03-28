#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QPushButton>

#include "subwidget.h"

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();

public slots:
    void showSubWidget();
    void showMainWidget();
    void showMainWidget1();
    void printText(int a, QString text);

private:
    QWidget subWidget;
    QPushButton* subButton;
    QPushButton* mainButton;
    SubWidget* subWidget1;
};

#endif // MAINWIDGET_H
