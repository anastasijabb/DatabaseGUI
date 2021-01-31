#ifndef UNIT_H
#define UNIT_H

#include <QDialog>
#include <QSqlDatabase>

class QSqlRelationalTableModel;
class QSqlRelationalDelegate;
class QSqlTableModel;

namespace Ui {
class Unit;
}

class Unit : public QDialog
{
   Q_OBJECT

public:
   explicit Unit(QWidget *parent = nullptr);
   ~Unit();

private slots:
   void on_pushButton_clicked();

   void on_pushButton_2_clicked();

   void on_pushButton_3_clicked();

private:
   Ui::Unit *ui;
   QSqlDatabase Database;
   QSqlRelationalDelegate *Delegate;
   QSqlRelationalTableModel *ModelUnit;
};

#endif // UNIT_H
