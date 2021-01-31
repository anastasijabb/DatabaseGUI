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

    ModelLueckentext->setRelation(2, QSqlRelation("Karteikarte", "ID", "WortEnglisch"));
    ModelLueckentext->setRelation(4, QSqlRelation("Karteikarte", "ID", "WortEnglisch"));
    ModelLueckentext->setRelation(6, QSqlRelation("Karteikarte", "ID", "WortEnglisch"));
    ModelLueckentext->select();


    ui->tableViewBuch->setModel(ModelLueckentext);
    ui->tableViewBuch->setItemDelegate(Delegate);
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
    QString id1,id2,id3;

    query.prepare("SELECT ID FROM Karteikarte WHERE WortEnglisch = ?");
    query.bindValue(0, luecke1);

    if( !query.exec() )
           qDebug() << "Fehler\n" << query.lastError();

    while (query.next()) {
            id1 = query.value(0).toString();
         }


    query.prepare("SELECT ID FROM Karteikarte WHERE WortEnglisch = ?");
    query.bindValue(0, luecke2);

    if( !query.exec() )
           qDebug() << "Fehler\n" << query.lastError();

    while (query.next()) {
            id2 = query.value(0).toString();
         }

    query.prepare("SELECT ID FROM Karteikarte WHERE WortEnglisch = ?");
    query.bindValue(0, luecke3);

    if( !query.exec() )
           qDebug() << "Fehler\n" << query.lastError();

    while (query.next()) {
            id3 = query.value(0).toString();
         }


    QString text1 = ui->textteil1->text();
    QString text2 = ui->textteil2->text();
    QString text3 = ui->textteil3->text();
    QString text4 = ui->textteil4->text();

    query.prepare("INSERT INTO Lueckentext (Textteil1, Luecke1, Textteil2, Luecke2, Textteil3, Luecke3, Textteil4) VALUES(?,?,?,?,?,?,?)");
    query.bindValue(0, text1);
    query.bindValue(1, id1.toInt());
    query.bindValue(2, text2);
    query.bindValue(3, id2.toInt());
    query.bindValue(4, text3);
    query.bindValue(5, id3.toInt());
    query.bindValue(6, text4);

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
