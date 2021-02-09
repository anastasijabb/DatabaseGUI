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
#include <QStandardPaths>

#include <QFileDialog>
#include <QMessageBox>

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
    ui->tableViewBuch->setColumnHidden(5, true);
    ui->tableViewBuch->setColumnHidden(6, true);
    ui->tableViewBuch->setColumnHidden(7, true);
    ui->tableViewBuch->setColumnHidden(8, true);
    ui->tableViewBuch->setColumnHidden(10, true);
    ui->tableViewBuch->setItemDelegate(Delegate);

    QSqlQuery query1;
    query1.prepare("SELECT Nummer FROM Unit");
    if( !query1.exec() )
           qDebug() << "Fehler\n" << query1.lastError();

    while (query1.next()) {
            ui->comboBox->addItem(query1.value(0).toString());
         }

}

Karteikarte::~Karteikarte()
{
    Database.close();
    delete ui;
}

void Karteikarte::on_pushButton_clicked()
{
    QSqlQuery query;

    query.prepare("INSERT INTO Karteikarte (WortEnglisch, WortDeutsch, BeispielsatzEnglisch, BeispielsatzDeutsch, AudioWort, AudioBeispielsatz, Bild, Feedback, Lueckentext1, Luecke, Lueckentext2) VALUES(?,?,?,?,?,?,?,?,?,?,?)" );

    QString bild_pfad = ui->label_4->text();
    QString audio_pfad = ui->label_9->text();
    QString audio2_pfad = ui->label_10->text();

    QString textteil1 = ui->textteil1->text();
    QString textteil2 = ui->textteil2->text();
    QString luecke = ui->luecke->text();

    QString VokabelEn = ui->VokabelEn->text();
    QString VokabelDe = ui->VokabelDe->text();
    QString BeispielEn = ui->BeispielEn->text();
    QString BeispielDe = ui->BeispielDe->text();
    QString Feedback = ui->Feedback->text();


    QFile file(bild_pfad);
    if (!file.open(QIODevice::ReadOnly)) return;
    QByteArray bildByteArray = file.readAll();

    QFile file2(audio_pfad);
    if (!file2.open(QIODevice::ReadOnly)) return;
    QByteArray audioByteArray = file2.readAll();

    QFile file3(audio2_pfad);
    if (!file3.open(QIODevice::ReadOnly)) return;
    QByteArray audio2ByteArray = file3.readAll();

    query.bindValue(0, VokabelEn);
    query.bindValue(1, VokabelDe);
    query.bindValue(2, BeispielEn);
    query.bindValue(3, BeispielDe);
    query.bindValue(4, audioByteArray);
    query.bindValue(5, audio2ByteArray);
    query.bindValue(6, bildByteArray);
    query.bindValue(7, Feedback);
    query.bindValue(8, textteil1);
    query.bindValue(9, luecke);
    query.bindValue(10, textteil2);

    if( !query.exec() )
           qDebug() << "Fehler\n" << query.lastError();

    query.prepare("SELECT ID FROM Karteikarte WHERE WortEnglisch = ? AND WortDeutsch = ?");
    query.bindValue(0, ui->VokabelEn->text());
    query.bindValue(1, ui->VokabelDe->text());
    int id;
    if( !query.exec() )
           qDebug() << "Fehler\n" << query.lastError();
    while (query.next()) {
            id = query.value(0).toInt();
         }

    query.prepare("INSERT INTO LektionKarte VALUES(?,?,?,?)");
    query.bindValue(0, id);
    query.bindValue(1, ui->comboBox_2->currentText().toInt());
    query.bindValue(2, ui->comboBox->currentText().toInt());
    //query.bindValue(3, "978-3-12-835021-9");
    query.bindValue(3, "978-3-12-835020-2");

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

void Karteikarte::on_comboBox_currentTextChanged(const QString &arg1)
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
