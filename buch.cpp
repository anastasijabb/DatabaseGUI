#include "buch.h"
#include "ui_buch.h"
#include <QSqlRelationalDelegate>
#include <QSqlRelationalTableModel>
#include <QSqlTableModel>
#include <QSqlError>
#include <QMessageBox>
#include <QSqlDriver>
#include <QSqlError>
#include <QDebug>
#include <QSqlQuery>

Buch::Buch(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Buch)
{
    ui->setupUi(this);

    Database = QSqlDatabase::addDatabase("QSQLITE");
    Database.setDatabaseName("C:/Users/Anastasija/Desktop/testdatenbank4.db");
    if (!Database.open()){
        QMessageBox::critical(this, "Error", Database.lastError().text());
        return;
    }


    ModelBuch = new QSqlRelationalTableModel(this);
    Delegate = new QSqlRelationalDelegate(this);

    ModelBuch->setTable("Buch");
    ModelBuch->select();

    ui->tableViewBuch->setModel(ModelBuch);
    ui->tableViewBuch->setItemDelegate(Delegate);
}

Buch::~Buch()
{
    Database.close();
    delete ui;
}

void Buch::on_pushButton_clicked()
{
    QSqlQuery query;

    query.prepare("INSERT INTO buch (ISBN, Titel, Klasse, Verlag) VALUES (?,?,?,?)");
    query.bindValue(0, ui->ISBN->text());
    query.bindValue(1, ui->Titel->text());
    query.bindValue(2, ui->Klasse->text().toInt());
    query.bindValue(3, ui->Verlag->text());

    if( !query.exec() )
           qDebug() << "Fehler\n" << query.lastError();

    ModelBuch->select();
    ui->ISBN->setText("");
    ui->Titel->setText("");
    ui->Klasse->setText("");
    ui->Verlag->setText("");
}



void Buch::on_pushButton_2_clicked()
{
    int deleteIndex = ui->deleteRow->text().toInt();
    ui->deleteRow->setText("");
    ModelBuch->removeRow(deleteIndex - 1);
    ModelBuch->select();
}
