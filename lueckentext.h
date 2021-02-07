#ifndef LUECKENTEXT_H
#define LUECKENTEXT_H

#include <QDialog>
#include <QSqlDatabase>

class QSqlRelationalTableModel;
class QSqlRelationalDelegate;
class QSqlTableModel;

namespace Ui {
class Lueckentext;
}

class Lueckentext : public QDialog
{
   Q_OBJECT

public:
   explicit Lueckentext(QWidget *parent = nullptr);
   ~Lueckentext();

private slots:

    void on_submit_clicked();

    void on_pushButton_2_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);

private:
   Ui::Lueckentext *ui;
   QSqlDatabase Database;
   QSqlRelationalDelegate *Delegate;
   QSqlRelationalTableModel *ModelLueckentext;
};

#endif // LUECKENTEXT_H
