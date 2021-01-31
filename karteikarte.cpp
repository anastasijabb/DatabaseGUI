#include "karteikarte.h"
#include "ui_karteikarte.h"

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
#include <QFileDialog>
#include <QMessageBox>
#include <QStandardPaths>

Karteikarte::Karteikarte(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Karteikarte)
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


    ModelKarteikarte = new QSqlRelationalTableModel(this);
    Delegate = new QSqlRelationalDelegate(this);

    ModelKarteikarte->setTable("Karteikarte");
    ModelKarteikarte->select();

    ui->tableViewBuch->setModel(ModelKarteikarte);
    ui->tableViewBuch->setItemDelegate(Delegate);
}

Karteikarte::~Karteikarte()
{
    Database.close();
    delete ui;
}

void Karteikarte::on_pushButton_clicked()
{
    QSqlQuery query;

    query.prepare("INSERT INTO Karteikarte (WortEnglisch, WortDeutsch, BeispielsatzEnglisch, BeispielsatzDeutsch, AudioWort, AudioBeispielsatz, Wortart, Bild, Feedback) VALUES(?,?,?,?,?,?,?,?,?)" );

    QString bild_pfad = ui->label_4->text();
    QString audio_pfad = ui->label_9->text();
    QString audio2_pfad = ui->label_10->text();

    QFile file(bild_pfad);
    if (!file.open(QIODevice::ReadOnly)) return;
    QByteArray bildByteArray = file.readAll();

    QFile file2(audio_pfad);
    if (!file2.open(QIODevice::ReadOnly)) return;
    QByteArray audioByteArray = file2.readAll();

    QFile file3(audio2_pfad);
    if (!file3.open(QIODevice::ReadOnly)) return;
    QByteArray audio2ByteArray = file3.readAll();

    query.bindValue(0, ui->VokabelEn->text());
    query.bindValue(1, ui->VokabelEn->text());
    query.bindValue(2, ui->BeispielEn->text());
    query.bindValue(3, ui->BeispielDe->text());
    query.bindValue(4, audioByteArray);
    query.bindValue(5, audio2ByteArray);
    query.bindValue(6, ui->Wortart->text());
    query.bindValue(7, bildByteArray);
    query.bindValue(8, ui->Feedback->text());

    if( !query.exec() )
           qDebug() << "Fehler\n" << query.lastError();

    ModelKarteikarte->select();
/*
    if( !query.exec( "SELECT AudioWort from Karteikarte" ))
           qDebug() << "Fehler beim Laden des Bildes aus der Datenbank:\n" << query.lastError();
       query.first();
       QByteArray outByteArray = query.value( 0 ).toByteArray();
       qDebug() << outByteArray; */
}



void Karteikarte::on_pushButton_2_clicked()
{
    int deleteIndex = ui->deleteRow->text().toInt();
    ui->deleteRow->setText("");
    ModelKarteikarte->removeRow(deleteIndex - 1);
    ModelKarteikarte->select();
}


void Karteikarte::on_pushButton_3_clicked()
{
    QString filter = "PNG (*.png)";
    QString file_name = QFileDialog::getOpenFileName(this, "Open file", "C://", filter);
    ui->label_4->setText(file_name);

     QFile file(file_name);
     if (!file.open(QIODevice::ReadOnly)) return;
     QByteArray inByteArray = file.readAll();

     QPixmap outPixmap = QPixmap();
     outPixmap.loadFromData( inByteArray );
     int w = ui->label_8->width();
     int h = ui->label_8->height();

     ui->label_8->setPixmap(outPixmap.scaled(w,h,Qt::KeepAspectRatio));

}

void Karteikarte::on_pushButton_4_clicked()
{
    QString filter = "WAV (*.wav)";
    QString file_name = QFileDialog::getOpenFileName(this, "Open file", "C://", filter);
    ui->label_9->setText(file_name);

    QFile audio(file_name);
    if (!audio.open(QIODevice::ReadOnly)) return;
    QByteArray inByteArray = audio.readAll();
}

void Karteikarte::on_pushButton_5_clicked()
{
    QString filter = "WAV (*.wav)";
    QString file_name = QFileDialog::getOpenFileName(this, "Open file", "C://", filter);
    ui->label_10->setText(file_name);

    QFile audio(file_name);
    if (!audio.open(QIODevice::ReadOnly)) return;
    QByteArray inByteArray = audio.readAll();
}
