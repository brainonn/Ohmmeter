#include "mainwindow.h"
#include "deviceform.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    on_tabWidget_tabBarClicked(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionUpdateCOMPortsList_triggered()
{

}


void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    int lastIndex = ui -> tabWidget -> count() - 1;
    if(index != lastIndex) return;
    ui -> tabWidget -> insertTab(lastIndex, new DeviceForm(),tr("Device %1").arg(lastIndex + 1));
    ui -> tabWidget -> setCurrentIndex(lastIndex);
}
