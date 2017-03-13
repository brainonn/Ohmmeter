#include "mainwindow.h"
#include "deviceform.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tabWidget = new QTabWidget(this);
    tabWidget -> addTab(new DeviceForm(),"Device 1");
    addTabButton = new QToolButton(tabWidget);
    addTabButton -> setIcon(QIcon(":/icons/Add.png"));
    tabWidget -> setCornerWidget(addTabButton);
    setCentralWidget(tabWidget);
    connect(addTabButton, SIGNAL(clicked()), this, SLOT(on_addTabButton_clicked()));


   /* ui -> tabWidget -> setTabIcon(0,QIcon("icons/Add.png"));
    on_tabWidget_tabBarClicked(0);*/
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionUpdateCOMPortsList_triggered()
{

}


void MainWindow::on_addTabButton_clicked()
{
    int deviceNumber = tabWidget -> count();
    tabWidget -> addTab(new DeviceForm(),tr("Device %1").arg(deviceNumber + 1));
    tabWidget -> setCurrentIndex(deviceNumber);
}


