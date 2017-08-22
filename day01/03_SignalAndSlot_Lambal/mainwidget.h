#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "subwidget.h"
#include <QWidget>
#include <QPushButton>


class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();
public   slots:
    void changeWindow();
    void changeWindow2();
    void dealSlot(int, QString);

private:
    QPushButton b1;
    QPushButton* b2;
    QPushButton b3;
    SubWidget sub;
};

#endif // MAINWIDGET_H
