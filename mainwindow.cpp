#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_comboBoxRate_currentIndexChanged(const QString &text)
{

}

void MainWindow::on_buttonAction_clicked()
{

}

void MainWindow::on_buttonRemote_clicked()
{

}

void MainWindow::on_comboBoxRange_currentIndexChanged(const QString &text)
{

}


void MainWindow::on_buttonZero_clicked()
{

}

void MainWindow::on_buttonScan_clicked()
{

}

void MainWindow::on_buttonSave_clicked()
{

}
void MainWindow::on_actionUpdateCOMPortsList_triggered()
{

}
