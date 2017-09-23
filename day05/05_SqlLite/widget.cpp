#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>   //db.lastError().text()
#include <QSqlQuery>
#include <QVariantList>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //打印Qt支持的数据库驱动
    qDebug()<<QSqlDatabase::drivers();

    //添加Sqlite数据库  关键字不支持累加
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../info.db");
    //打开数据库
    if(false == db.open()){
        QMessageBox::warning(this, "错误", db.lastError().text());
        return;
    }
//    else{
//        QMessageBox::about(this, "MySQL数据库", "恭喜你，正确打开数据库");
//    }
    QSqlQuery query;
    //关键字不支持累加  auto_increment
    query.exec("create table student(id int primary key , "
               "name varchar(255), age int, score int);");



    //插入
    //QSqlQuery query;
    //query.exec("insert into student(id, name, age) values(1, 'mike', 18);");

    //批量插入
    //odbc风格
    //预处理语句
    // ? 相当于 占位符
    //注意声明的顺序student(name, age, score)  这个决定了QVariantList的顺序
//    query.prepare("insert into student(name, age, score) values(?, ?, ?)");
//    //给字段设置内容 list
//    QVariantList nameList;
//    nameList<<"xiaoming"<<"小龙"<<"xiaojiang";
//    QVariantList ageList;
//    ageList<<11<<22<<33;
//    QVariantList scoreList;
//    scoreList<<59<<69<<79;
//    //给字段绑定相应的值，按顺序绑定
//    query.addBindValue(nameList);
//    query.addBindValue(ageList);
//    query.addBindValue(scoreList);
//    //执行预处理命令
//    if (!query.execBatch()) {
//            QMessageBox::critical(0, QObject::tr("Database Error"),
//                                  query.lastError().text());
//        }

    //oracle风格
    query.prepare("insert into student(id, name, age, score) "
                  "values(:id, :name, :age, :score)");
    //给字段设置内容 list  这个地方必须顺序
    QVariantList id;
    id<<123<<111<<223;
    QVariantList nameList;
    nameList<<"小明"<<"xiaoming"<<"小江";
    QVariantList ageList;
    ageList<<11<<22<<33;
    QVariantList scoreList;
    scoreList<<59<<69<<79;
    //给字段绑定相应的值，可以自定义顺序进行绑定
    query.bindValue(":id", id);
    query.bindValue(":age", ageList);

    query.bindValue(":name", nameList);

    query.bindValue(":score", scoreList);

    //执行预处理命令
    if (!query.execBatch()) {
        QMessageBox::critical(0, QObject::tr("Database Error"),
                              query.lastError().text());
    }

    //查询
    query.exec("select * from student;");
    while(query.next()){
        //取出当前行的内容
        qDebug()<<query.value(0).toInt()
               <<query.value(1).toString()
              <<query.value("age").toInt()
             <<query.value("score").toInt();
    }
}

Widget::~Widget()
{
    delete ui;
}
