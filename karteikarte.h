#ifndef KARTEIKARTE_H
#define KARTEIKARTE_H

#include <QDialog>
#include <QSqlDatabase>

class QSqlRelationalTableModel;
class QSqlRelationalDelegate;
class QSqlTableModel;

namespace Ui {
class Karteikarte;
}

class Karteikarte : public QDialog
{
   Q_OBJECT

public:
   explicit Karteikarte(QWidget *parent = nullptr);
   ~Karteikarte();

private slots:
   void on_pushButton_clicked();
   void on_pushButton_2_clicked();
   void on_pushButton_3_clicked();

   void on_pushButton_4_clicked();
   void on_pushButton_5_clicked();

private:
   Ui::Karteikarte *ui;
   QSqlDatabase Database;
   QSqlRelationalDelegate *Delegate;
   QSqlRelationalTableModel *ModelKarteikarte;
};

#endif // KARTEIKARTE_H
