#ifndef SUBWIDGET_H
#define SUBWIDGET_H

#include <QWidget>
class QPushButton;

class SubWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SubWidget(QWidget *parent = nullptr);

signals:
    void changeSlot();
    void changeSlot(int, QString);

public slots:
    void emitChangeSlot();
    void emitPrintSignal();

private:
    QPushButton* subclassButton;
};

#endif // SUBWIDGET_H
