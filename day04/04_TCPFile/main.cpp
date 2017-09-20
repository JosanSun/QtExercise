#include "serverwidget.h"
#include "clienwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ServerWidget w;
    w.show();

    ClienWidget w2;
    w2.show();
    return a.exec();
}
