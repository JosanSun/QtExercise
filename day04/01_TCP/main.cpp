#include "tcpserverwidget.h"
#include "tcpclientwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    TcpServerWidget server;
    server.show();
    TcpClientWidget client;
    client.show();

    return a.exec();
}
