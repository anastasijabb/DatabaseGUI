#ifndef BUCH_H
#define BUCH_H

#include <QDialog>
#include <QSqlDatabase>

class QSqlRelationalTableModel;
class QSqlRelationalDelegate;
class QSqlTableModel;

namespace Ui {
class Buch;
}

class Buch : public QDialog
{
    Q_OBJECT

public:
    explicit Buch(QWidget *parent = nullptr);
    ~Buch();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Buch *ui;
    QSqlDatabase Database;
    QSqlRelationalDelegate *Delegate;
    QSqlRelationalTableModel *ModelBuch;
};

#endif // BUCH_H
