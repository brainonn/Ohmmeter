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
    tabWidget -> setTabsClosable(true);
    addTabButton = new QToolButton(tabWidget);
    addTabButton -> setIcon(QIcon(":/icons/Add.png"));
    tabWidget -> setCornerWidget(addTabButton);
    setCentralWidget(tabWidget);
    setFixedSize(geometry().width(), geometry().height()); //dirty hack
    connect(addTabButton, SIGNAL(clicked()), this, SLOT(on_addTabButton_clicked()));
    connect(tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(on_tabWidget_tabCloseRequested(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionUpdateCOMPortsList_triggered()
{
    int deviceNumber = tabWidget -> count();
    for(int i = 0; i < deviceNumber; i++) {
        (qobject_cast<DeviceForm*> (tabWidget -> widget(i))) -> updatePorts(); //casting QWidget* to DeviceForm*, not sure if it works

    }
}


void MainWindow::on_addTabButton_clicked()
{
    int deviceNumber = tabWidget -> count();
    tabWidget -> addTab(new DeviceForm(),tr("Device %1").arg(deviceNumber + 1));
    tabWidget -> setCurrentIndex(deviceNumber);
}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    int deviceNumber = tabWidget -> count();
    if (deviceNumber == 1) this -> close();
    else {
        tabWidget -> removeTab(index);
        for(int i = 0; i < deviceNumber; i++) {
            tabWidget -> setTabText(i, tr("Device %1").arg(i + 1));
        }
    }
}

