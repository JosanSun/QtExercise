#ifndef TCPCLIENTWIDGET_H
#define TCPCLIENTWIDGET_H

#include <QWidget>
#include <QTcpSocket>

class QPlainTextEdit;

namespace Ui {
class TcpClientWidget;
}

class TcpClientWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TcpClientWidget(QWidget *parent = 0);
    ~TcpClientWidget();

private slots:
    void on_pushButtonConnect_clicked();

    void on_pushButtonSend_clicked();

    void on_pushButtonClose_clicked();

private:
    bool isTextEditEmpty(const QPlainTextEdit* textEdit) const;

    Ui::TcpClientWidget *ui;
    QTcpSocket* tcpSocket;
};

#endif // TCPCLIENTWIDGET_H
