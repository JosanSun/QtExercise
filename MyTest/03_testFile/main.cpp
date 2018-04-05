//#include <QApplication>
//#include <QFile>
//#include <QTextStream>
//#include <QTime>
//#include <QDebug>

//#define qcout qDebug()

//void testFile01()
//{
//    QFile inFile(":/test/testFile-ANSI-win.txt");
//    if (!inFile.open(QIODevice::ReadOnly | QIODevice::Text))
//        return;

//    QFile outFile("../testFile-ANSI-win-readline-bak.txt");
//    if (!outFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
//        return;

//    // inFile.copy("../001.txt");     // 这个也会移动文件指针

//    QTextStream in(&inFile);
//    QTextStream out(&outFile);
//    out.setCodec("UTF-8");

//    while (!in.atEnd())
//    {
//        QString line = in.readLine();
//        out << line;
//        if(!line.isNull())
//        {
//            out << endl;
//        }
//    }
//}

//void testFile02()
//{
//    QFile inFile(":/test/longLine.txt");
//    if (!inFile.open(QIODevice::ReadOnly | QIODevice::Text))
//        return;

//    QFile outFile("../testFile-ANSI-win-readline-bak.txt");
//    if (!outFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
//        return;

//    // inFile.copy("../001.txt");     // 这个也会移动文件指针

//    QTextStream in(&inFile);
//    QTextStream out(&outFile);
//    out.setCodec("UTF-8");

//    while (!in.atEnd())
//    {
//        QString line = in.readLine();
//        out << line;
//        qcout << line;
//        if(!line.isNull())
//        {
//            out << "\r\n";
//        }
//    }
//}

//// read write可能是最好的函数，但是没有分行，他们将文件按字符进行读取，一个汉字一个字符，
//// 注意\r\n会换成\n，这样就没有换行符的丢失。
//void testFile03()
//{
//    QFile inFile(":/test/test03.txt");
//    if (!inFile.open(QIODevice::ReadOnly | QIODevice::Text))
//        return;

//    QFile outFile("../003.txt");
//    if (!outFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
//        return;

//    while(!inFile.atEnd())
//    {
//        QByteArray arr = inFile.read(3);
//        qcout << arr;
//        outFile.write(arr);
//    }
//}

//void testFile04()
//{
//    QFile inFile(":/test/test04.txt");
//    if (!inFile.open(QIODevice::ReadOnly | QIODevice::Text))
//        return;

//    QFile outFile("../004.txt");
//    if (!outFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
//        return;

//    while(!inFile.atEnd())
//    {
//        QByteArray arr = inFile.read(3);
//        qcout << arr;
//        outFile.write(arr);
//    }
//}

//void testFile05()
//{
//    QFile inFile(":/test/test03.txt");
//    if (!inFile.open(QIODevice::ReadOnly | QIODevice::Text))
//        return;

//    QFile outFile("../003-readline.txt");
//    if (!outFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
//        return;

//    QTextStream in(&inFile);
//    QTextStream out(&outFile);
//    QString line;

//    bool first = true;

//    while (!in.atEnd())
//    {
//        if(!first)
//        {
//            out << endl;
//        }
//        else
//        {
//            first = false;
//        }
//        line = in.readLine();
//        out << line;
//    }

//    if(line.isEmpty())
//    {
//        out << endl;
//    }
//}

//// readLine()可以实现完美复制
//void testFile06()
//{
//    QFile inFile(":/te/test/test04.txt");
//    if (!inFile.open(QIODevice::ReadOnly | QIODevice::Text))
//        return;

//    QFile outFile("../004-readline.txt");
//    if (!outFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
//        return;

//    QTextStream in(&inFile);
//    QTextStream out(&outFile);
//    QString line;

//    bool first = true;

//    while (!in.atEnd())
//    {
//        if(!first)
//        {
//            out << endl;
//        }
//        else
//        {
//            first = false;
//        }
//        line = in.readLine();
//        out << line;
//    }

//    if(line.isEmpty())
//    {
//        out << endl;
//    }
//}

//void testFile07()
//{

//    QFile inFile("../03_testFile/file/bigdata03.txt");
//    if (!inFile.open(QIODevice::ReadOnly | QIODevice::Text))
//    {
//        qcout << inFile.errorString();
//        return ;
//    }

//    QFile outFile("../bigdata-read-02.txt");
//    if (!outFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
//        return;

//    QTime time1, time2;
//    time1 = QTime::currentTime();
//    while(!inFile.atEnd())
//    {
//        QByteArray arr = inFile.read(3*1024);
//        outFile.write(arr);
//        //qcout << arr;
////        for(int i = 0; i < 10; ++i)
////        {
////            outFile.write(arr);
////        }
//    }
//    time2 = QTime::currentTime();
//    qcout << time1.msecsTo(time2);
//}

//void testFile08()
//{
//    QFile inFile("../03_testFile/file/bigdata03.txt");
//    if (!inFile.open(QIODevice::ReadOnly | QIODevice::Text))
//        return;

//    QFile outFile("../bigdata-readall-02.txt");
//    if (!outFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
//        return;

//    QTime time1, time2, time3;
//    time1 = QTime::currentTime();

//    QByteArray arr = inFile.readAll();
//    qcout << arr.size();
//    time3 = QTime::currentTime();
////    qcout << time1.msecsTo(time3);
////    outFile.write(arr);
//    outFile.write(inFile.readAll());

////    while(!inFile.atEnd())
////    {
////        QByteArray arr = inFile.read(4*1024);
////        //qcout << arr;
////        outFile.write(arr);
////    }
//    time2 = QTime::currentTime();
//    qcout << time1.msecsTo(time2);

//}

//int main(int argc, char *argv[])
//{

////        testFile01();
////        testFile02();
////    testFile03();
////    qcout << "-------------";
////    testFile04();

////    testFile05();
////    testFile06();
//    //qcout << "This is a BUG";
//    //testFile07();
//    testFile08();

//    return 0;
//}
