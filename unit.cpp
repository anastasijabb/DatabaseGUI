#include "unit.h"
#include "ui_unit.h"
#include <QSqlRelationalDelegate>
#include <QSqlRelationalTableModel>
#include <QSqlTableModel>
#include <QSqlError>
#include <QMessageBox>
#include <QSqlDriver>
#include <QSqlError>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QStandardPaths>
#include <QFileDialog>
#include <QMessageBox>


Unit::Unit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Unit)
{
    ui->setupUi(this);

    Database = QSqlDatabase::addDatabase("QSQLITE");

    QString dbpath =
              QString("%1/testdatenbank4.db").arg(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation));

    Database.setDatabaseName(dbpath);


    if (!Database.open()){
        QMessageBox::critical(this, "Error", Database.lastError().text());
        return;
    }

    QSqlQuery query;
    if (!query.exec("PRAGMA foreign_keys = ON"))
        qCritical() << "QSQLQuery::exec";


    ModelUnit = new QSqlRelationalTableModel(this);
    Delegate = new QSqlRelationalDelegate(this);

    ModelUnit->setTable("Unit");
    //ModelUnit->setRelation(2, QSqlRelation("buch", "ISBN", "Titel"));
    ModelUnit->select();

    ui->tableViewBuch->setModel(ModelUnit);
    ui->tableViewBuch->setItemDelegate(Delegate);
}

Unit::~Unit()
{
    Database.close();
    delete ui;
}

void Unit::on_pushButton_clicked()
{

    QSqlQuery query;

    query.prepare("INSERT INTO unit (Nummer, Name, Buch) VALUES (?,?,?)");
    query.bindValue(0, ui->Nummer->text().toInt());
    query.bindValue(1, ui->Name->text());
    query.bindValue(2, "978-3-12-835021-9");

    if( !query.exec() )
           qDebug() << "Fehler\n" << query.lastError();

    ModelUnit->select();
    ui->Nummer->setText("");
    ui->Name->setText("");
}



void Unit::on_pushButton_2_clicked()
{
    int deleteIndex = ui->deleteRow->text().toInt();
    ui->deleteRow->setText("");
    ModelUnit->removeRow(deleteIndex - 1);
    ModelUnit->select();
}
