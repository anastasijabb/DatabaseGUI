#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "buch.h"
#include "unit.h"
#include "lektion.h"
#include "karteikarte.h"
#include "schueler.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
    Buch *buch;
    Unit *unit;
    Lektion *lektion;
    Karteikarte *karteikarte;
    Schueler *schueler;
};
#endif // MAINWINDOW_H
