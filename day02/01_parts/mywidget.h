#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>

class QSpinBox;
class QSlider;
class QHBoxLayout;

class MyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent = nullptr);

signals:

public slots:

private:
    QSpinBox* spinBox;
    QSlider* slider;
    QHBoxLayout* layout;
};

#endif // MYWIDGET_H
