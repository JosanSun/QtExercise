#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QTime>
#include <QDebug>
#define qcout qDebug()

void testFile07()
{
    QFile inFile("../03_testFile/file/bigdata03.txt");
    if (!inFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qcout << inFile.errorString();
        return ;
    }

    QFile outFile("../bigdata-read-02.txt");
    if (!outFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
        return;

    QTime time1, time2;
    time1 = QTime::currentTime();
    while(!inFile.atEnd())
    {
        QByteArray arr = inFile.read(3*1024);
        outFile.write(arr);
    }
    time2 = QTime::currentTime();
    qcout << time1.msecsTo(time2);
}

void testFile08()
{
    QFile inFile("../03_testFile/file/bigdata03.txt");
    if (!inFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QFile outFile("../bigdata-readall-02.txt");
    if (!outFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
        return;

    QTime time1, time2, time3;
    time1 = QTime::currentTime();

    QByteArray arr = inFile.readAll();
    qcout << arr.size();
    time3 = QTime::currentTime();
    outFile.write(inFile.readAll());

    time2 = QTime::currentTime();
    qcout << time1.msecsTo(time2);

}

int main(int argc, char *argv[])
{
    testFile07();
    //testFile08();

    return 0;
}
