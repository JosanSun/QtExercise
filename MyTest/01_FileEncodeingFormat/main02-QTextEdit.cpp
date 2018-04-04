#include <QApplication>
#include <QTextEdit>
#include <QFile>

#include "myheaders.h"

#define TEST(testFile) void testWidget##testFile()

TEST(ANSI)
{
    QFile inFile(":/test/test-ANSI.txt");
    if (!inFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QByteArray inArray = inFile.readAll();

    qcout << inArray;                             // "----\nI love you!\n\xCE\xD2\xB0\xAE\xC4\xE3\xA3\xA1\n\xA1\xA3\xA1\xA3\xA1\xA3\n1234\n1234"
    qcout << inArray.data();  // 与最下面的data相同
    qcout << QString(inArray);                    // "----\nI love you!\n?????\n??????\n1234\n1234"
    QString in(inArray);
    qcout << in;                                  // "----\nI love you!\n?????\n??????\n1234\n1234"
    qcout << in.toUtf8().data();
    //    ----
    //    I love you!
    //    ?????
    //    ??????
    //    1234
    //    1234

    QTextEdit* textEdit = new QTextEdit;
    textEdit->show();
    textEdit->setText(in);
}

TEST(GB2312)
{
    QFile inFile(":/test/test-GB2312.txt");
    if (!inFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QByteArray inArray = inFile.readAll();

    qcout << inArray;                             // "----\nI love you!\n\xCE\xD2\xB0\xAE\xC4\xE3\xA3\xA1\n\xA1\xA3\xA1\xA3\xA1\xA3\n1234\n1234"
    qcout << inArray.data();  // 与最下面的data相同
    qcout << QString(inArray);                    // "----\nI love you!\n?????\n??????\n1234\n1234"
    QString in(inArray);
    qcout << in;                                  // "----\nI love you!\n?????\n??????\n1234\n1234"
    qcout << in.toUtf8().data();
    //    ----
    //    I love you!
    //    ?????
    //    ??????
    //    1234
    //    1234

    QTextEdit* textEdit = new QTextEdit;
    textEdit->show();
    textEdit->setText(in);
}

TEST(utf8BOM)
{
    QFile inFile(":/test/test-utf8-BOM.txt");
    if (!inFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QByteArray inArray = inFile.readAll();

    qcout << inArray;                             //"\xEF\xBB\xBF----\nI love you!\n\xE6\x88\x91\xE7\x88\xB1\xE4\xBD\xA0\xEF\xBC\x81\n\xE3\x80\x82\xE3\x80\x82\xE3\x80\x82\n1234\n1234"
    qcout << inArray.data();  // 与最下面的data相同
    qcout << QString(inArray);                    //"----\nI love you!\n我爱你！\n。。。\n1234\n1234"
    QString in(inArray);
    qcout << in;                                  //"----\nI love you!\n我爱你！\n。。。\n1234\n1234"
    qcout << in.toUtf8().data();
//    ----
//    I love you!
//    我爱你！
//    。。。
//    1234
//    1234

    QTextEdit* textEdit = new QTextEdit;
    textEdit->show();
    textEdit->setText(in);
}

TEST(utf8)
{
    QFile inFile(":/test/test-utf8.txt");
    if (!inFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QByteArray inArray = inFile.readAll();

    qcout << inArray;                             // "----\nI love you!\n\xE6\x88\x91\xE7\x88\xB1\xE4\xBD\xA0\xEF\xBC\x81\n\xE3\x80\x82\xE3\x80\x82\xE3\x80\x82\n1234\n1234"
    qcout << inArray.data();  // 与最下面的data相同
    qcout << QString(inArray);                    // "----\nI love you!\n我爱你！\n。。。\n1234\n1234"
    QString in(inArray);
    qcout << in;                                  // "----\nI love you!\n我爱你！\n。。。\n1234\n1234"
    qcout << in.toUtf8().data();
    //    ----
    //    I love you!
    //    我爱你！
    //    。。。
    //    1234
    //    1234

    QTextEdit* textEdit = new QTextEdit;
    textEdit->show();
    textEdit->setText(in);
}


int main02(int argc, char* argv[])
{
    QApplication app(argc, argv);

    testWidgetANSI();            // 未能正确显示
    testWidgetGB2312();          // 未能正确显示
    testWidgetutf8BOM();         // 正确显示
    testWidgetutf8();            // 正确显示

    return app.exec();
}
