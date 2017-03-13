#include "deviceform.h"
#include "ui_deviceform.h"

DeviceForm::DeviceForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeviceForm)
{
    ui->setupUi(this);
}

DeviceForm::~DeviceForm()
{
    delete ui;
}
void DeviceForm::updatePorts()
{
    ui -> comboBoxPorts -> clear();
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        ui -> comboBoxPorts -> addItem(info.portName());
    }

}

void DeviceForm::on_comboBoxRate_currentIndexChanged(const QString &text)
{

}

void DeviceForm::on_buttonAction_clicked()
{

}

void DeviceForm::on_buttonRemote_clicked()
{

}

void DeviceForm::on_comboBoxRange_currentIndexChanged(const QString &text)
{

}


void DeviceForm::on_buttonZero_clicked()
{

}

void DeviceForm::on_buttonScan_clicked()
{

}

void DeviceForm::on_buttonSave_clicked()
{

}
