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
}

Lueckentext::~Lueckentext()
{
    delete ui;
}
