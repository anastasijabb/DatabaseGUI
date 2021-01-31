#include "choice.h"
#include "ui_choice.h"

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

Choice::Choice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Choice)
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


    ModelChoice = new QSqlRelationalTableModel(this);
    Delegate = new QSqlRelationalDelegate(this);

    ModelChoice->setTable("Choice");

    ModelChoice->setRelation(3, QSqlRelation("Karteikarte", "ID", "WortEnglisch"));
    ModelChoice->setRelation(4, QSqlRelation("Karteikarte", "ID", "WortEnglisch"));
    ModelChoice->setJoinMode((QSqlRelationalTableModel::JoinMode) 1);

    ModelChoice->select();

    ui->tableViewBuch->setModel(ModelChoice);
    ui->tableViewBuch->setItemDelegate(Delegate);

    ui->radio1->setChecked(true);
}

Choice::~Choice()
{
    Database.close();
    delete ui;
}

void Choice::on_submit_clicked()
{
    QString aufgabe = ui->aufgabe->text();
    QString loesung1 = ui->loesung1->text();
    QString loesung2 = ui->loesung2->text();

    bool multipleChoice = ui->radio2->isChecked();

    QSqlQuery query;
    QString id1,id2;

    query.prepare("SELECT ID FROM Karteikarte WHERE WortEnglisch = ?");
    query.bindValue(0, loesung1);

    if( !query.exec() )
           qDebug() << "Fehler\n" << query.lastError();

    while (query.next()) {
            id1 = query.value(0).toString();
         }


    if(multipleChoice) {
        query.prepare("SELECT ID FROM Karteikarte WHERE WortEnglisch = ?");
        query.bindValue(0, loesung2);

        if( !query.exec() )
               qDebug() << "Fehler\n" << query.lastError();

        while (query.next()) {
                id2 = query.value(0).toString();
             }
    }


    if(multipleChoice) {
        query.prepare("INSERT INTO Choice (Typ, Aufgabe, Loesung1, Loesung2) VALUES (?, ?, ?, ?)");
        query.bindValue(0, "Multiple");
        query.bindValue(1, aufgabe);
        query.bindValue(2, id1.toInt());
        query.bindValue(3, id2.toInt());
    } else {
        query.prepare("INSERT INTO Choice (Typ, Aufgabe, Loesung1, Loesung2) VALUES (?, ?, ?, NULL)");
        query.bindValue(0, "Single");
        query.bindValue(1, aufgabe);
        query.bindValue(2, id1.toInt());
    }

    if( !query.exec() )
           qDebug() << "Fehler\n" << query.lastError();

    ModelChoice->select();
}
