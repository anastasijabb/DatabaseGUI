#ifndef LEKTION_H
#define LEKTION_H

#include <QDialog>
#include <QSqlDatabase>

class QSqlRelationalTableModel;
class QSqlRelationalDelegate;
class QSqlTableModel;

namespace Ui {
class Lektion;
}

class Lektion : public QDialog
{
   Q_OBJECT

public:
   explicit Lektion(QWidget *parent = nullptr);
   ~Lektion();

private slots:
   void on_pushButton_clicked();

   void on_pushButton_2_clicked();

private:
   Ui::Lektion *ui;
   QSqlDatabase Database;
   QSqlRelationalDelegate *Delegate;
   QSqlRelationalTableModel *ModelLektion;
};

#endif // UNIT_H
