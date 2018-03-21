#include <QApplication>
#include <QWidget>
#include <QPushButton>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QWidget w;
    // 默认窗口标题是生成的TARGET的名字
    w.setWindowTitle(QObject::tr("主要看气质"));
    w.show();

    QPushButton b;
    b.setText("^_^");
    b.show();

    QPushButton* b1 = new QPushButton;
    b1->setParent(&w);
    b1->setText("Hello Qt");
    b1->hide();       // NOTE:b1->show()  b1->hide()  对后面w.show()的影响

    //w.update();

    w.show();   //w.show()真正含义，是显示父对象以及子对象的默认值都设置为显示。（一般默认的都是隐藏）
    return app.exec();
}
