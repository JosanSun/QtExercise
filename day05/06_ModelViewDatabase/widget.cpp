#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>   //db.lastError().text()
#include <QSqlQuery>
#include <QVariantList>
#include <QSqlRecord>
#include <QModelIndexList>

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
    db.setDatabaseName("world");

    //打开数据库
    if(false == db.open()){
        QMessageBox::warning(this, "错误", db.lastError().text());
        return;
    }
    //设置模型
    model = new QSqlTableModel(this);
    model->setTable("country");     //指定使用哪个表

    //把model放在view
    ui->tableView->setModel(model);

    //显示model里的数据    不是show()
    model->select();

    //设置标题显示内容，不会修改数据里面的内容
    //model->setHeaderData(0, Qt::Horizontal, "学号");
    //model->setHeaderData(1, Qt::Horizontal, "姓名");

    //设置 model的编辑模式，手动提交修改
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    //设置view中的数据库不允许修改  默认是可以直接修改的
    //ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_buttonAdd_clicked()
{
    //添加空记录
    QSqlRecord rec = model->record();
    //获取行号
    int row = model->rowCount();
    model->insertRecord(row, rec);
}

void Widget::on_buttonSure_clicked()
{
    model->submitAll();   //提交动作
}

void Widget::on_buttonCancel_clicked()
{
    //取消所有动作
    model->revertAll();
    //提交动作
    model->submitAll();
}

void Widget::on_buttonDelete_clicked()
{
    //选取选中的模型
    QItemSelectionModel *sModel = ui->tableView->selectionModel();
    //取出模型中的索引
    QModelIndexList list = sModel->selectedRows();
    //删除所有选中的行
    for(int i=0;i<list.size();++i){
        //const T &QList::at(int i) const
        //int QModelIndex::row() const
        model->removeRow(list.at(i).row());
    }

}

//注意：这个不需要点击“确定”，就能生成选择
void Widget::on_buttonFind_clicked()
{
    QString name = ui->lineEdit->text();
    //'%1' 这个冒号不能少
    QString str = QString("name = '%1'").arg(name);

    model->setFilter(str);
    //显示内容
    model->select();
}
