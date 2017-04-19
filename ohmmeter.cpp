#include "ohmmeter.h"
#include <QDebug>

bool Readings::operator!=(const Readings& arg) const {
    return (this -> value != arg.value) || (this -> units != arg.units);
}

Ohmmeter::Ohmmeter() : QObject()
{
    serial = new QSerialPort();
    timer = new QTimer();
    time = new QTime(0,0,0,0);
    QObject::connect(timer,SIGNAL(timeout()),this, SLOT(getCurrentReadings()));

}

Ohmmeter::~Ohmmeter()
{
    if(serial -> isOpen()) disconnect();
    delete serial;
    delete timer;
}


bool Ohmmeter::connect(QString &portName)
{
    serial -> setPortName(portName);
    serial -> setBaudRate(baudrate);
    serial -> setParity(parity);
    serial -> setDataBits(dataBits);
    serial -> setStopBits(stopBits);
    if(!serial -> open(QIODevice::ReadWrite)) {
        return false;
    }
    setRemote(true);
    timer -> start(updateInterval);
    getCurrentReadings();
    return true;

}

void Ohmmeter::disconnect()
{
    if(timer -> isActive()) timer -> stop();
    int i = 0;
    do {
        setRemote(false);
        i++;
    } while(getResponse() != "[OK]" && i <= 500);
    serial -> close();

}

void Ohmmeter::setRemote(bool enabled)
{
    TimerHandler handler(timer);
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
    TimerHandler handler(timer);
    QString commSetRange = "[R" + QString::number(range) + "]";
    serial -> write(commSetRange.toLocal8Bit());
}

void Ohmmeter::setRate(int rate)
{
    TimerHandler handler(timer);
    QString commSetRate = "[F" + QString::number(rate) + "]";
    serial -> write(commSetRate.toLocal8Bit());
}

void Ohmmeter::getCurrentReadings()
{
    QString commGetReadings = "[?D]";
    Readings previous = currentReadings;
    double elapsedTime = 0;
    serial -> write(commGetReadings.toLocal8Bit());
    QString response = getResponse();
    if(isKineticsRunning) elapsedTime = 0.001 * (time -> elapsed() - additionalWaitTime);
    currentReadings = parseReadingsString(response);
    if(isKineticsRunning) {
        kinetics.append(currentReadings, elapsedTime);
        emit(dataReady(kinetics));
    }
    if(previous != currentReadings) emit(readingsChanged(currentReadings));




}

QString Ohmmeter::getResponse() const
{
    TimerHandler handler(timer);
    QByteArray tmp;
    if(serial->waitForReadyRead(firstWaitTime)) {
        tmp = serial->readAll();
        while (serial->waitForReadyRead(additionalWaitTime)) tmp += serial->readAll();
    }
    QString response = QString(tmp);
    return response;

}

Readings Ohmmeter::parseReadingsString(const QString& str)
{
    QString value;
    QString units;
    for(int i = 2; i < str.length() - 1; i++) {
        if(str[i].isNumber() || str[i] == '.') {
            value.append(str[i]);
        } else if(str[i].isLetter()) {
            units.append(str[i]);
        }
    }
    if(value.startsWith('0') && value.indexOf('.') > 1) {
        value.remove(0, value.indexOf('.') - 1);
    }
    units.remove(0, units.indexOf(QRegExp("[m, K, M]?Ohm")));
    Readings res;
    res.value = value.toDouble();
    res.units = units;
    return res;
}

void Ohmmeter::setKineticsRunning(bool running)
{
    if(running) {
        kinetics.clear();
        time -> start();
    }
    isKineticsRunning = running;
}

Readings::operator double() {
    double multiplier = 1;
    if (this -> units == "mOhm") multiplier = 0.001;
    else if(this -> units == "Ohm") multiplier = 1;
    else if(this -> units == "KOhm") multiplier = 1000;
    else if(this -> units == "MOhm") multiplier = 1000000;
    return value * multiplier;
}

KineticsData& Ohmmeter::getKinetics()
{
    return kinetics;
}





