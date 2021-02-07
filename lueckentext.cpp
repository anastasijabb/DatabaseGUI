#include "lueckentext.h"
#include "ui_lueckentext.h"
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

Lueckentext::Lueckentext(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Lueckentext)
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


    ModelLueckentext = new QSqlRelationalTableModel(this);
    Delegate = new QSqlRelationalDelegate(this);

    ModelLueckentext->setTable("Lueckentext");

    ModelLueckentext->select();


    ui->tableViewBuch->setModel(ModelLueckentext);
    ui->tableViewBuch->setItemDelegate(Delegate);

    QSqlQuery query1;
    query1.prepare("SELECT Nummer FROM Unit");
    if( !query1.exec() )
           qDebug() << "Fehler\n" << query1.lastError();

    while (query1.next()) {
            ui->comboBox->addItem(query1.value(0).toString());
         }
}

Lueckentext::~Lueckentext()
{
    delete ui;
}

void Lueckentext::on_submit_clicked()
{
    QString luecke1 = ui->luecke1->text();
    QString luecke2 = ui->luecke2->text();
    QString luecke3 = ui->luecke3->text();
    QSqlQuery query;

    QString text1 = ui->textteil1->text();
    QString text2 = ui->textteil2->text();
    QString text3 = ui->textteil3->text();
    QString text4 = ui->textteil4->text();

    query.prepare("INSERT INTO Lueckentext (Textteil1, Luecke1, Textteil2, Luecke2, Textteil3, Luecke3, Textteil4, Lektion, Unit, Buch) VALUES(?,?,?,?,?,?,?,?,?,?)");
    query.bindValue(0, text1);
    query.bindValue(1, luecke1);
    query.bindValue(2, text2);
    query.bindValue(3, luecke2);
    query.bindValue(4, text3);
    query.bindValue(5, luecke3);
    query.bindValue(6, text4);
    query.bindValue(7, ui->comboBox_2->currentText().toInt());
    query.bindValue(8, ui->comboBox->currentText().toInt());
    query.bindValue(9, "978-3-12-835021-9");

    if( !query.exec() )
           qDebug() << "Fehler\n" << query.lastError();

    ModelLueckentext->select();
    ui->textteil1->setText("");
    ui->textteil2->setText("");
    ui->textteil3->setText("");
    ui->textteil4->setText("");
    ui->luecke1->setText("");
    ui->luecke2->setText("");
    ui->luecke3->setText("");


}

void Lueckentext::on_pushButton_2_clicked()
{
    int deleteIndex = ui->deleteRow->text().toInt();
    ui->deleteRow->setText("");
    ModelLueckentext->removeRow(deleteIndex - 1);
    ModelLueckentext->select();
}

void Lueckentext::on_comboBox_currentTextChanged(const QString &arg1)
{
    ui->comboBox_2->clear();
    int unit = arg1.toInt();
    QSqlQuery query1;

    query1.prepare("SELECT Nummer FROM Lektion WHERE Unit = ?");
    query1.bindValue(0, unit);
    if( !query1.exec() )
           qDebug() << "Fehler\n" << query1.lastError();

    while (query1.next()) {
            ui->comboBox_2->addItem(query1.value(0).toString());
         }
}
