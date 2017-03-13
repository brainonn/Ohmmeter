#ifndef DEVICEFORM_H
#define DEVICEFORM_H

#include <QWidget>
#include <QSerialPort>
#include <QSerialPortInfo>
#include "qcustomplot.h"

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
private slots:
    void on_buttonAction_clicked();
    void on_buttonRemote_clicked();
    void on_buttonScan_clicked();
    void on_buttonSave_clicked();
    void on_buttonZero_clicked();
    void on_comboBoxRate_currentIndexChanged(const QString &text);
    void on_comboBoxRange_currentIndexChanged(const QString &text);
private:
    Ui::DeviceForm *ui;
    QSerialPort *serialPort;
};

#endif // DEVICEFORM_H
