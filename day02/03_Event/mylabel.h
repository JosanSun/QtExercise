#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>
class QMouseEvent;

class MyLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MyLabel(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent* ev);
    void mouseReleaseEvent(QMouseEvent* ev);
    void mouseMoveEvent(QMouseEvent* ev);
    void enterEvent(QEvent* /* ev */);
    void leaveEvent(QEvent* /* ev */);
    bool event(QEvent* ev);
};

#endif // MYLABEL_H
