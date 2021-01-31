#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    buch = new Buch(this);
    buch->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    unit = new Unit(this);
    unit->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    lektion = new Lektion(this);
    lektion->show();
}

void MainWindow::on_pushButton_4_clicked()
{
    karteikarte = new Karteikarte(this);
    karteikarte->show();
}

void MainWindow::on_pushButton_5_clicked()
{
    lueckentext = new Lueckentext(this);
    lueckentext->show();
}
