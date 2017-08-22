#include <QApplication>
#include <QWidget>
#include <QPushButton>

int main(int argc, char** argv){


    QApplication app(argc, argv);


    QWidget w;
    //设置标题
    w.setWindowTitle(QString::fromLocal8Bit("主要看气质"));



    //注意此时，关闭窗口w以及按钮b才能正常结束程序
    QPushButton b;
    b.setText("^_^");
    b.show();
    //可以多次显示show()
    b.setText("123");
    b.show();

    //指定父对象，两种一个ctor，另一个通过成员函数

    QPushButton b1;
    b1.setText("@_@");
    b1.setParent(&w);
    b1.move(100, 100);

    QPushButton b2(&w);
    b2.setText("test");
    b2.move(50, 50);
    //b1.show();
    //注意w.show()必须在这最后，如果在创建b1之前，就显示的话。之后，b1显示不出来。
    w.show();

    return app.exec();
}
