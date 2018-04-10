#ifndef ServerWidget_H
#define ServerWidget_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>

class QPlainTextEdit;

namespace Ui {
class ServerWidget;
}

class ServerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ServerWidget(QWidget *parent = nullptr);
    ~ServerWidget();

private slots:
    void on_pushButtonSend_clicked();

    void on_pushButtonClose_clicked();

private:
    bool isTextEditEmpty(const QPlainTextEdit* textEdit) const;
    Ui::ServerWidget *ui = nullptr;

    QTcpServer* tcpServer = nullptr;
    QTcpSocket* tcpSocket = nullptr;
};

#endif // ServerWidget_H
