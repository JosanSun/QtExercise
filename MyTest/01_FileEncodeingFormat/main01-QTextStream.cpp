// 学习笔记：  QTextStream
/*
QTextStream is guessing the codec based on the input file contents,
for the non BOM utf-8 file it guesses incorrectly.

You should call in.setCodec() if you know the format of your input files,
if you don't know the format you will have to continue relying on
Qt's guesses or write your own encoding detector.
*/

// 此测试文件的编码格式Utf8, 测试环境是QtCreator Mingw32bit

// 从文件输入
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QTextEdit>
#include <QTextCodec>

#include "myheaders.h"

#define TEST(testFile) void test##testFile()

TEST(ANSI)
{
    QFile inFile(":/test/test-ANSI.txt");
    if (!inFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QFile outFile("../test-ANSI-bak.txt");
    if (!outFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
        return;

    QTextStream in(&inFile);
    QTextStream out(&outFile);
    out.setCodec("UTF-8");

//    QString text = in.readAll();  //读入换行时，用\n表示 数组中没有EOF字符
//    out << text;

    // 这样写入会去掉换行符号
    while (!in.atEnd()) {
        QString line = in.readLine();    // 注意：readLine()当中没有换行符。
        out << line;
    }
}

TEST(GB2312)
{
    QFile inFile(":/test/test-GB2312.txt");
    if (!inFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QFile outFile("../test-GB2312-bak.txt");
    if (!outFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
        return;

    QTextStream in(&inFile);
    QTextStream out(&outFile);
    out.setCodec("UTF-8");

    while (!in.atEnd()) {
        QString line = in.readLine();
        out << line;
    }
}

TEST(utf8BOM)
{
    QFile inFile(":/test/test-utf8-BOM.txt");
    if (!inFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QFile outFile("../test-utf8-BOM-bak.txt");
    if (!outFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
        return;

    QTextStream in(&inFile);
    QTextStream out(&outFile);
    out.setCodec("UTF-8");

    while (!in.atEnd()) {
        QString line = in.readLine();
        out << line;
    }
}

TEST(utf8)
{
    QFile inFile(":/test/test-utf8.txt");
    if (!inFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QFile outFile("../test-utf8-bak.txt");
    if (!outFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
        return;

    // 可能存在中文乱码
    QTextStream in(&inFile);
    in.setCodec("UTF-8");   // 去掉的话，无法正确解析UTF-8. 也就是说默认的解析失效。

    QTextStream out(&outFile);
    out.setCodec("UTF-8");
    // out.setGenerateByteOrderMark(false);  // 输出文件的格式 UTF-8, 这是默认的格式
    // out.setGenerateByteOrderMark(true);   // 输出文件的格式 UTF-8 BOM

    while (!in.atEnd()) {
        // QByteArray line = in.readLine().toUtf8();
        // QString line = QString(in.readLine().toUtf8());
        QString line = in.readLine();
        out << line;
    }
}

// 从字符串输入
void test()
{
    QFile outFile("../test-QString-bak.txt");
    if (!outFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
        return;

    QTextStream out(&outFile);
    out.setCodec("UTF-8");

    // 输出文件的编码始终是utf8
    out << QObject::tr("我爱你"); // 可以正确显示
    out << "01我爱你01";          // 无法正确显示
}

// 从qcout输出
void test01()
{
    // 没有出现乱码
    qcout << "01我爱你";               // 01我爱你
    qcout << QObject::tr("01我爱你");  // "01我爱你"
}


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    testANSI();
//    testGB2312();
//    testutf8BOM();
//    testutf8();
//    test();
//    test01();

    return app.exec();
}



