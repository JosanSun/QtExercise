#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QWidget>
#include <QFile>
#include <QTcpSocket>

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
    void on_buttonConnect_clicked();

private:
    Ui::ClientWidget *ui;

    QTcpSocket* tcpSocket;
    QFile file;
    QString fileName;
    qint64 fileSize;
    qint64 recvSize;
    bool isStart;
};

#endif // CLIENTWIDGET_H
