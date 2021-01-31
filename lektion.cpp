#include "lektion.h"
#include "ui_lektion.h"
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


Lektion::Lektion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Lektion)
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


    ModelLektion = new QSqlRelationalTableModel(this);
    Delegate = new QSqlRelationalDelegate(this);

    ModelLektion->setTable("Lektion");
    ModelLektion->select();

    ui->tableViewBuch->setModel(ModelLektion);
    ui->tableViewBuch->setItemDelegate(Delegate);
}

Lektion::~Lektion()
{
    Database.close();
    delete ui;
}

void Lektion::on_pushButton_clicked()
{
    QSqlQuery query;

    query.prepare("INSERT INTO lektion (Nummer, Name, Film, Unit, Buch) VALUES(?, ?, ?, ?, ?)" );

    query.bindValue(0, ui->Nummer->text().toInt());
    query.bindValue(1, ui->Name->text());
    query.bindValue(2, ui->Film->text());
    query.bindValue(3, ui->Unit->text().toInt());
    query.bindValue(4, ui->Buch->text());

    if( !query.exec() )
           qDebug() << "Fehler\n" << query.lastError();


    ModelLektion->select();
    ui->Nummer->setText("");
    ui->Name->setText("");
    ui->Buch->setText("");
    ui->Unit->setText("");
    ui->Film->setText("");
}



void Lektion::on_pushButton_2_clicked()
{
    int deleteIndex = ui->deleteRow->text().toInt();
    ui->deleteRow->setText("");
    ModelLektion->removeRow(deleteIndex - 1);
    ModelLektion->select();
}

