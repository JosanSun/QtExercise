#include <QApplication>
#include <QTextEdit>
#include <QFile>
#include <QTextCodec>

#include "myheaders.h"

#define TEST(testFile) void testWidget02##testFile()


TEST(ANSI)
{
    QTextEdit* textEdit = new QTextEdit;
    textEdit->show();

    QFile inFile(":/test/test-ANSI.txt");
    if (!inFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextCodec::ConverterState state;
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");


    const QByteArray data = inFile.readAll();
    const QString text = codec->toUnicode(data.constData(), data.size(), &state);
    qcout << text;
    if (state.invalidChars > 0)
    {
        // Not a UTF-8 text - using system default locale
        QTextCodec * codec = QTextCodec::codecForLocale();
        if (!codec)
            return;
        qcout << "invalidChars > 0";
        textEdit->setPlainText(codec->toUnicode(data));
    }
    else
    {
        qcout << "invalidChars = 0";
        textEdit->setPlainText(text);
    }
}

TEST(GB2312)
{
    QTextEdit* textEdit = new QTextEdit;
    textEdit->show();

    QFile inFile(":/test/test-GB2312.txt");
    if (!inFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextCodec::ConverterState state;
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");


    const QByteArray data = inFile.readAll();
    const QString text = codec->toUnicode(data.constData(), data.size(), &state);
    qcout << text;
    if (state.invalidChars > 0)
    {
        // Not a UTF-8 text - using system default locale
        QTextCodec * codec = QTextCodec::codecForLocale();
        if (!codec)
            return;
        qcout << "invalidChars > 0";
        textEdit->setPlainText(codec->toUnicode(data));
    }
    else
    {
        qcout << "invalidChars = 0";
        textEdit->setPlainText(text);
    }
}

TEST(utf8BOM)
{
    QTextEdit* textEdit = new QTextEdit;
    textEdit->show();

    QFile inFile(":/test/test-utf8-BOM.txt");
    if (!inFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextCodec::ConverterState state;
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");


    const QByteArray data = inFile.readAll();
    const QString text = codec->toUnicode(data.constData(), data.size(), &state);
    qcout << text;
    if (state.invalidChars > 0)
    {
        // Not a UTF-8 text - using system default locale
        QTextCodec * codec = QTextCodec::codecForLocale();
        if (!codec)
            return;
        qcout << "invalidChars > 0";
        textEdit->setPlainText(codec->toUnicode(data));
    }
    else
    {
        qcout << "invalidChars = 0";
        textEdit->setPlainText(text);
    }
}

TEST(utf8)
{
    QTextEdit* textEdit = new QTextEdit;
    textEdit->show();

    QFile inFile(":/test/test-utf8.txt");
    if (!inFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    const QByteArray data = inFile.readAll();

    QTextCodec::ConverterState state;
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    const QString text = codec->toUnicode(data.constData(), data.size(), &state);
    qcout << text;
    if (state.invalidChars > 0)
    {
        // Not a UTF-8 text - using system default locale
        QTextCodec * codec = QTextCodec::codecForLocale();
        if (!codec)
            return;
        qcout << "invalidChars > 0";
        textEdit->setPlainText(codec->toUnicode(data));
    }
    else
    {
        qcout << "invalidChars = 0";
        textEdit->setPlainText(text);
    }
}


//-----------------------------------------------------------------------------
// QTextCodec::codecForUtfText()使用系统来识别编码方式的时候，无法识别不带BOM的Unicode编码

#define TEST01(testFile) void testWidget03##testFile()

TEST01(ANSI)
{
    QTextEdit* textEdit = new QTextEdit;
    textEdit->show();

    QFile inFile(":/test/test-ANSI.txt");
    if (!inFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return;


    char *str = "UTF-8";
    QTextCodec* code = QTextCodec::codecForName(str);
    QByteArray name = code->name();
    qcout << name; // "UTF-8"

    const QByteArray byteArray = inFile.readAll();
    QTextCodec *codec = QTextCodec::codecForUtfText(byteArray, QTextCodec::codecForName("System"));
    qcout << codec->name();  // "System"
    const QString text = codec->toUnicode(byteArray);
    qcout << text;
}

TEST01(GB2312)
{
    QTextEdit* textEdit = new QTextEdit;
    textEdit->show();

    QFile inFile(":/test/test-GB2312.txt");
    if (!inFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    const QByteArray byteArray = inFile.readAll();
    QTextCodec *codec = QTextCodec::codecForUtfText(byteArray, QTextCodec::codecForName("System"));
    qcout << codec->name();  // "System"
    const QString text = codec->toUnicode(byteArray);
    qcout << text;
}

TEST01(utf8BOM)
{
    QTextEdit* textEdit = new QTextEdit;
    textEdit->show();

    QFile inFile(":/test/test-utf8-BOM.txt");
    if (!inFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    const QByteArray byteArray = inFile.readAll();
    QTextCodec *codec = QTextCodec::codecForUtfText(byteArray, QTextCodec::codecForName("System"));
    qcout << codec->name();  // "UTF-8"    注意这里从System --> UTF-8
    const QString text = codec->toUnicode(byteArray);
    qcout << text;
}

TEST01(utf8)
{
    QTextEdit* textEdit = new QTextEdit;
    textEdit->show();

    QFile inFile(":/test/test-utf8.txt");
    if (!inFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    const QByteArray byteArray = inFile.readAll();
    QTextCodec *codec = QTextCodec::codecForUtfText(byteArray, QTextCodec::codecForName("System"));
    qcout << codec->name();  // "System"
    const QString text = codec->toUnicode(byteArray);
    qcout << text;
}


int main03(int argc, char* argv[])
{
    QApplication app(argc, argv);

//    testWidget02ANSI();       // 未能正确显示
//    testWidget02GB2312();     // 未能正确显示
//    testWidget02utf8BOM();    // 正确显示
//    testWidget02utf8();       // 正确显示
    testWidget03ANSI();        // 正确显示
    testWidget03GB2312();      // 正确显示
    testWidget03utf8BOM();     // 正确显示
    testWidget03utf8();        // 未能正确显示  原因与main01-QTextStream.cpp相同，系统无法识别无BOM的Utf8文件

    return app.exec();
}
