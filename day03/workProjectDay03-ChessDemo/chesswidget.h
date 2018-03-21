#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

namespace Ui {
class ChessWidget;
}

class ChessWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChessWidget(QWidget *parent = 0);
    ~ChessWidget();

protected:
    void paintEvent(QPaintEvent* ev);
    void mousePressEvent(QMouseEvent* ev);

private:
    Ui::ChessWidget *ui;

    int gridW;              // 棋盘格子的宽度与高度
    int gridH;
    int startX;
    int startY;             // 棋盘起点x, y坐标

    int chessX, chessY;     // 棋盘下标
};

#endif //  CHESSWIDGET_H
