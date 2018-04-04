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
    explicit TcpServerWidget(QWidget *parent = nullptr);
    ~TcpServerWidget();

private slots:
    void on_pushButtonSend_clicked();

    void on_pushButtonClose_clicked();

private:
    bool isTextEditEmpty(const QPlainTextEdit* textEdit) const;
    Ui::TcpServerWidget *ui = nullptr;

    QTcpServer* tcpServer = nullptr;
    QTcpSocket* tcpSocket = nullptr;
};

#endif // TCPSERVERWIDGET_H
