#ifndef ClientWidget_H
#define ClientWidget_H

#include <QWidget>
#include <QTcpSocket>

class QPlainTextEdit;

namespace Ui {
class ClientWidget;
}

class ClientWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClientWidget(QWidget *parent = 0);
    ~ClientWidget();

private slots:
    void on_pushButtonConnect_clicked();

    void on_pushButtonSend_clicked();

    void on_pushButtonClose_clicked();

private:
    bool isTextEditEmpty(const QPlainTextEdit* textEdit) const;

    Ui::ClientWidget *ui;
    QTcpSocket* tcpSocket;
};

#endif // ClientWidget_H
