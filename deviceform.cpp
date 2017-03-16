#include "deviceform.h"
#include "ui_deviceform.h"

DeviceForm::DeviceForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeviceForm)
{
    ui->setupUi(this);
    updatePorts();
    ohmmeter = new Ohmmeter();
    connect(ohmmeter, SIGNAL(remoteChanged(bool)), this, SLOT(on_remoteChanged(bool)));

}

DeviceForm::~DeviceForm()
{
    delete ohmmeter;
    delete ui;
}
void DeviceForm::updatePorts()
{
    ui -> comboBoxPorts -> clear();
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        ui -> comboBoxPorts -> addItem(info.portName());
    }

}

void DeviceForm::on_comboBoxRange_currentIndexChanged(int index)
{
    ohmmeter -> setRange(index + 1);
}

void DeviceForm::on_buttonAction_clicked()
{

    if (ui -> buttonAction -> text() == "Connect") {
        QString currentPortName = ui -> comboBoxPorts -> currentText();
        if(ohmmeter -> connect(currentPortName)) {
            ui -> buttonAction -> setText("Disconect");
            ui -> buttonRemote -> setEnabled(true);
    }
    }
    else {

        on_buttonRemote_clicked();
        ohmmeter -> disconnect();
        ui -> buttonAction -> setText("Connect");
        ui -> buttonRemote -> setEnabled(false);

    }

}

void DeviceForm::on_buttonRemote_clicked()
{
    if (ui -> buttonRemote -> text() == "Enable") ohmmeter -> setRemote(true);
    else ohmmeter -> setRemote(false);
}

void DeviceForm::on_comboBoxRate_currentIndexChanged(int index)
{
    ohmmeter -> setRate(index);
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

void DeviceForm::on_remoteChanged(bool enabled)
{
    if(enabled) ui -> buttonRemote -> setText("Disable");
    else ui -> buttonRemote -> setText("Enable");
    ui -> buttonScan -> setEnabled(enabled);
    ui -> buttonSave -> setEnabled(enabled);
    ui -> buttonZero -> setEnabled(enabled);
    ui -> comboBoxRange -> setEnabled(enabled);
    ui -> comboBoxRate -> setEnabled(enabled);
    if(enabled) {
        QStringList ranges;
        ranges.append("20 mOhm");
        ranges.append("200 mOhm");
        ranges.append("2 Ohm");
        ranges.append("20 Ohm");
        ranges.append("200 Ohm");
        ranges.append("2 kOhm");
        ranges.append("20 kOhm");
        ranges.append("200 kOhm");
        ranges.append("2 MOhm");
        ranges.append("Auto");
        ui -> comboBoxRange -> addItems(ranges);
        ui -> comboBoxRange -> setCurrentText("Auto");
        QStringList rates;
        rates.append("Fast");
        rates.append("Slow");
        ui -> comboBoxRate -> addItems(rates);
        ui -> comboBoxRate -> setCurrentText("Fast");
    } else {
        ui -> comboBoxRange -> clear();
        ui -> comboBoxRate -> clear();
    }

}
