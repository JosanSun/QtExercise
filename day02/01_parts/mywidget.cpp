#include <QSpinBox>
#include <QSlider>
#include <QHBoxLayout>

#include "mywidget.h"

MyWidget::MyWidget(QWidget *parent) : QWidget(parent)
{
    spinBox = new QSpinBox(this);
    slider = new QSlider(Qt::Horizontal, this);

    layout = new QHBoxLayout(this);
    layout->addWidget(spinBox);
    layout->addWidget(slider);
    //setLayout(layout);

    connect(spinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            slider, &QSlider::setValue);
    connect(slider, &QSlider::valueChanged,
            spinBox, &QSpinBox::setValue);
}
