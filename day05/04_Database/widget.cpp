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

    //添加MySql数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    //连接数据库
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("1234");
    db.setDatabaseName("test01");

    //打开数据库
    if(false == db.open()){
        QMessageBox::warning(this, "错误", db.lastError().text());
        return;
    }
//    else{
//        QMessageBox::about(this, "MySQL数据库", "恭喜你，正确打开数据库");
//    }
//    QSqlQuery query;
//    query.exec("create table student(id int primary key auto_increment, "
//               "name varchar(255), age int, score int);");


//    //添加第二个MySql数据库  连接
//    QSqlDatabase db1 = QSqlDatabase::addDatabase("QMYSQL", "a");
//    //连接数据库
//    db1.setHostName("127.0.0.1");
//    db1.setUserName("root");
//    db1.setPassword("1234");
//    db1.setDatabaseName("test01");

//    //打开数据库
//    if(false == db1.open()){
//        QMessageBox::warning(this, "错误", db.lastError().text());
//        return;
//    }
////    else{
////        QMessageBox::about(this, "MySQL数据库", "恭喜你，正确打开数据库");
////    }
//    //必须对于第二个数据库，必须指定数据库名称
//    QSqlQuery query1(db1);
//    query1.exec("create table student(id int primary key auto_increment, "
//               "name varchar(255), age int, score int);");


//    //现将前面的注释掉   添加第三个MySql数据库  连接
//    QSqlDatabase db1 = QSqlDatabase::addDatabase("QMYSQL", "b");
//    //连接数据库
//    db1.setHostName("127.0.0.1");
//    db1.setUserName("root");
//    db1.setPassword("1234");
//    db1.setDatabaseName("test02");

//    //打开数据库
//    if(false == db1.open()){
//        QMessageBox::warning(this, "错误", db.lastError().text());
//        return;
//    }
////    else{
////        QMessageBox::about(this, "MySQL数据库", "恭喜你，正确打开数据库");
////    }
//    //必须对于第二个数据库，必须指定数据库名称
//    //否则的话，默认与QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
//    //这个进行连接
//    QSqlQuery query1;
//    query1.exec("create table student(id int primary key auto_increment, "
//               "name varchar(255), age int, score int);");
    //插入
    QSqlQuery query;
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

//    //oracle风格
//    query.prepare("insert into student(name, age, score) "
//                  "values(:name, :age, :score)");
//    //给字段设置内容 list
//    QVariantList nameList;
//    nameList<<"小明"<<"xiaoming"<<"小江";
//    QVariantList ageList;
//    ageList<<11<<22<<33;
//    QVariantList scoreList;
//    scoreList<<59<<69<<79;
//    //给字段绑定相应的值，可以自定义顺序进行绑定

//    query.bindValue(":age", ageList);

//    query.bindValue(":name", nameList);

//    query.bindValue(":score", scoreList);

//    //执行预处理命令
//    if (!query.execBatch()) {
//        QMessageBox::critical(0, QObject::tr("Database Error"),
//                              query.lastError().text());
//    }

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

void Widget::on_buttonDelete_clicked()
{
    //获取行编辑内容
    QString name = ui->lineEdit->text();
    QString sqlDel = QString("delete from student where name = '%1';").arg(name);

    //开始事务
    QSqlDatabase::database().transaction();
    QSqlQuery query;
    query.exec(sqlDel);
}

void Widget::on_buttonSure_clicked()
{
    //确定删除
    QSqlDatabase::database().commit();
}

void Widget::on_buttonCancel_clicked()
{
    //取消删除
    QSqlDatabase::database().rollback();
}
