#include <QPainter>
#include <QMouseEvent>

#include "chesswidget.h"
#include "ui_chesswidget.h"

ChessWidget::ChessWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChessWidget)
{
    ui->setupUi(this);

    chessX = -1;
    chessY = -1;
}

ChessWidget::~ChessWidget()
{
    delete ui;
}


void ChessWidget::paintEvent(QPaintEvent * /* ev */)
{
    gridW = width() / 10;
    gridH = height() / 10;

    startX = gridW;
    startY = gridH;

    QPainter p(this);
    p.drawPixmap(rect(), QPixmap(":/images/bk-source.jpg"));

    QPen pen;
    pen.setWidth(4);
    p.setPen(pen);

    for(int i = 0; i < 9; ++i)
    {
        p.drawLine(startX, startY + i * gridH, startX + 8 * gridW, startY + i * gridH);
        p.drawLine(startX + i * gridW, startY, startX + i * gridW, startY + 8 * gridH);
    }
    if(chessX != -1 && chessY != -1)
    {
        p.drawPixmap(startX + chessX * gridW, startY + chessY * gridH,
                     gridW, gridH,
                     QPixmap(":/images/smile.png"));
    }
}

void ChessWidget::mousePressEvent(QMouseEvent *ev)
{
    int x = ev->x();
    int y = ev->y();
    chessX = x / gridW - 1;
    chessY = y / gridH - 1;
    if(chessX <= 7 && chessX >= 0 && chessY <=7 && chessY >=0)
    {
        update();
    }
}
