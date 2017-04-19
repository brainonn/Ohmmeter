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
    connect(ohmmeter, SIGNAL(readingsChanged(Readings)), this, SLOT(on_readingsChanged(Readings)));
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
    if(ui -> comboBoxPorts -> count() != 0) {
        ui -> buttonAction -> setEnabled(true);
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
        } else {
            QMessageBox msg;
            msg.setText("Can't connect to the device on port " + currentPortName);
            msg.exec();
        }
    }
    else {
        ohmmeter -> disconnect();
        ui -> lcdNumber -> display(0);
        ui -> buttonAction -> setText("Connect");
        ui -> buttonRemote -> setEnabled(false);
        ui -> plotWidget -> clearGraphs();

    }

}

void DeviceForm::on_buttonRemote_clicked()
{
    if (ui -> buttonRemote -> text() == "Enable") {
        ohmmeter -> setRemote(true);
    }
    else {
        ohmmeter -> setRemote(false);
    }
}

void DeviceForm::on_comboBoxRate_currentIndexChanged(int index)
{
    ohmmeter -> setRate(index);
}

void DeviceForm::on_buttonScan_clicked()
{
    if(ui -> buttonScan -> text() == "Start") {
        ui -> plotWidget -> clearGraphs();
        ui -> plotWidget -> addGraph();
        connect(ohmmeter, SIGNAL(dataReady(const KineticsData&)), this, SLOT(kineticsTick(const KineticsData&)));
        ui -> buttonScan -> setText("Stop");
        ohmmeter -> setKineticsRunning(true);

    } else {
        disconnect(ohmmeter, SIGNAL(dataReady(const KineticsData&)), this, SLOT(kineticsTick(const KineticsData&)));
        ohmmeter -> setKineticsRunning(false);
        ui -> buttonScan -> setText("Start");


    }


}

void DeviceForm::on_buttonSave_clicked()
{
    QString filename = "kinetics.txt";
    QFile file(filename);
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QMessageBox msg;
        msg.setText("Can't open file");
        msg.exec();
        return;
    }
    QTextStream out(&file);
    out << ohmmeter -> getKinetics();
    file.close();

}

void DeviceForm::on_remoteChanged(bool enabled)
{
    if(enabled) ui -> buttonRemote -> setText("Disable");
    else ui -> buttonRemote -> setText("Enable");
    ui -> buttonScan -> setEnabled(enabled);
    ui -> buttonSave -> setEnabled(enabled);
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

void DeviceForm::on_readingsChanged(const Readings& readings)
{
    ui -> lcdNumber -> display(readings.value);
    QString units = readings.units;
    if(units == "mOhm") {
        ui -> radioButtonUnits_mOhm -> setChecked(true);
    } else if(units == "Ohm") {
        ui -> radioButtonUnits_Ohm -> setChecked(true);
    } else if(units == "KOhm") {
        ui -> radioButtonUnits_kOhm -> setChecked(true);
    } else if(units == "MOhm") {
        ui -> radioButtonUnits_MOhm -> setChecked(true);
    }
}


void DeviceForm::kineticsTick(const KineticsData& arg) const
{

    ui -> plotWidget -> graph(0) -> addData(arg.getLastTime(), arg.getLastValue());
    ui -> plotWidget -> xAxis -> setRange(0,arg.getMaxTime());
    ui -> plotWidget -> yAxis -> setRange(0,arg.getMaxValue());
    ui -> plotWidget -> replot();

}

