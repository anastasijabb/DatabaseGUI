#ifndef CHOICE_H
#define CHOICE_H

#include <QDialog>
#include <QSqlDatabase>

class QSqlRelationalTableModel;
class QSqlRelationalDelegate;
class QSqlTableModel;

namespace Ui {
class Choice;
}

class Choice : public QDialog
{
   Q_OBJECT

public:
   explicit Choice(QWidget *parent = nullptr);
   ~Choice();


private slots:
    void on_submit_clicked();

private:
   Ui::Choice *ui;
   QSqlDatabase Database;
   QSqlRelationalDelegate *Delegate;
   QSqlRelationalTableModel *ModelChoice;
};
#endif // CHOICE_H
