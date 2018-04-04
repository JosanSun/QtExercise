void on_buttonSelectFile_clicked();
#ifndef SERVERWIDGET_H
#define SERVERWIDGET_H

#include <QWidget>
#include <QTcpServer>   //监听套接字
#include <QTcpSocket>   //通信套接字
#include <QFile>

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
    void on_buttonSend_clicked();
    void on_buttonClose_clicked();

private:
    void initButtons();
    void changeButtons();

    Ui::ServerWidget *ui  = nullptr;

    QTcpServer *tcpServer = nullptr;  //监听套接字
    QTcpSocket *tcpSocket = nullptr;  //通信套接字

    QString fileName;
    quint64 fileSize;
    qint64 sendSize;
    QFile file;
};

#endif // SERVERWIDGET_H
