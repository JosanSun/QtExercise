#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QPushButton>

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();

    void mySlot();

private:
    QPushButton b1;
    QPushButton* b2;
};

#endif // MAINWIDGET_H
