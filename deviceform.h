#ifndef DEVICEFORM_H
#define DEVICEFORM_H

#include <QWidget>
#include <QSerialPortInfo>
#include <QFile>
#include <QMessageBox>
#include "qcustomplot.h"
#include "ohmmeter.h"

namespace Ui {
class DeviceForm;
}

class DeviceForm : public QWidget
{
    Q_OBJECT

public:
    explicit DeviceForm(QWidget *parent = 0);
    ~DeviceForm();
    void updatePorts();

public slots:
    void on_buttonAction_clicked();
    void on_buttonRemote_clicked();
    void on_buttonScan_clicked();
    void on_buttonSave_clicked();
    void on_comboBoxRate_currentIndexChanged(int index);
    void on_comboBoxRange_currentIndexChanged(int index);
    void on_remoteChanged(bool remoteEnabled);
    void on_readingsChanged(const Readings& readings);
    void kineticsTick(const KineticsData& arg) const;


private:
    Ui::DeviceForm *ui;
    Ohmmeter *ohmmeter;
};

#endif // DEVICEFORM_H
