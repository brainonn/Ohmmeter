#ifndef OHMMETER_H
#define OHMMETER_H

#include <QSerialPort>
#include <QTimer>
#include <QRegExp>
#include <kineticsdata.h>
#include <timerhandler.h>


enum Range {r20m = 1, r200m, r2, r20, r200, r2k, r20k, r200k, r2M};
enum Rate {fast, slow};
const int firstWaitTime = 50;
const int additionalWaitTime = 10;
const int updateInterval = 100;
struct Readings {
    double value = 0;
    QString units = "mOhm";
    operator double();
    bool operator!=(const Readings& arg) const;
};


class Ohmmeter : public QObject {
    Q_OBJECT
private:
    QSerialPort *serial;
    static const int baudrate = 9600;
    static const QSerialPort::Parity parity = QSerialPort::NoParity;
    static const QSerialPort::DataBits dataBits = QSerialPort::Data8;
    static const QSerialPort::StopBits stopBits = QSerialPort::OneStop;
    QTimer* timer;
    QTime *time;
    Readings currentReadings;
    KineticsData kinetics;
    bool isKineticsRunning = false;

signals:
    void remoteChanged(bool remoteEnabled);
    void readingsChanged(Readings readings);
    void dataReady(const KineticsData& arg) const;
public slots:
    void getCurrentReadings();

public:
    Ohmmeter();
    ~Ohmmeter();
    bool connect(QString &portName);
    void disconnect();
    void setRemote(bool enabled);
    void setRange(int range);
    void setRate (int rate);
    void autoSetRange();
    Range getRange() const;
    Rate getRate() const;
    QString getResponse() const;
    Readings parseReadingsString(const QString& str);
    void setKineticsRunning(bool running);
    KineticsData& getKinetics();




};








#endif // OHMMETER_H
