#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPushButton>

class QMouseEvent;

class MyButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyButton(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent* ev);
};

#endif // MYBUTTON_H
