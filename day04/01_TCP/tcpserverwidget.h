#ifndef TCPSERVERWIDGET_H
#define TCPSERVERWIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>

class QPlainTextEdit;

namespace Ui {
class TcpServerWidget;
}

class TcpServerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TcpServerWidget(QWidget *parent = 0);
    ~TcpServerWidget();

private slots:
    void on_pushButtonSend_clicked();

    void on_pushButtonClose_clicked();

private:
    bool isTextEditEmpty(const QPlainTextEdit* textEdit) const;
    Ui::TcpServerWidget *ui;

    QTcpServer* tcpServer;
    QTcpSocket* tcpSocket;
};

#endif // TCPSERVERWIDGET_H
