#include "smallwidget.h"
#include <QSpinBox>
#include <QSlider>
#include <QHBoxLayout>


SmallWidget::SmallWidget(QWidget *parent) : QWidget(parent)
{
    QSpinBox* spin = new QSpinBox(this);
    QSlider* slider = new QSlider(Qt::Horizontal,this);

    QHBoxLayout* hLayout = new QHBoxLayout;
    hLayout->addWidget(spin);
    hLayout->addWidget(slider);

    setLayout(hLayout);
    //注意书写格式
    connect(spin, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            slider, &QSlider::setValue);
    connect(slider, static_cast<void (QSlider::*)(int)>(&QSlider::valueChanged),
            spin, &QSpinBox::setValue);
}
