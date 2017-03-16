#include "ohmmeter.h"
#include <QMessageBox>

Ohmmeter::Ohmmeter() : QObject()
{
    serial = new QSerialPort();
}

Ohmmeter::~Ohmmeter()
{
    delete serial;
}

bool Ohmmeter::connect(QString &portName)
{
    serial -> setPortName(portName);
    serial -> setBaudRate(baudrate);
    serial -> setParity(parity);
    serial -> setDataBits(dataBits);
    serial -> setStopBits(stopBits);
    if(!serial -> open(QIODevice::ReadWrite)) {
        QMessageBox msg;
        msg.setText("Can't connect to the device on port " + portName);
        msg.exec();
        return false;
    }
    setRemote(true);
    return true;

}

void Ohmmeter::disconnect()
{
    serial -> close();
}

void Ohmmeter::setRemote(bool enabled)
{
    if(enabled) {
        QString commEnableRemote = "[+]";
        serial -> write(commEnableRemote.toLocal8Bit());
    } else {
        QString commDisableRemote = "[-]";
        serial -> write(commDisableRemote.toLocal8Bit());
    }
    emit remoteChanged(enabled);
}

void Ohmmeter::setRange(int range)
{
    QString commSetRange = "[R" + QString::number(range) + "]";
    serial -> write(commSetRange.toLocal8Bit());
}

void Ohmmeter::setRate(int rate)
{
    QString commSetRate = "[F" + QString::number(rate) + "]";
    serial -> write(commSetRate.toLocal8Bit());
}

