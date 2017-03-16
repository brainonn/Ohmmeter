#ifndef OHMMETER_H
#define OHMMETER_H

#include <QSerialPort>


enum Range {r20m = 1, r200m, r2, r20, r200, r2k, r20k, r200k, r2M};
enum Rate {fast, slow};



class Ohmmeter : public QObject {
    Q_OBJECT
private:
    QSerialPort *serial;
    double currentReadings;
    static const int baudrate = 9600;
    static const QSerialPort::Parity parity = QSerialPort::NoParity;
    static const QSerialPort::DataBits dataBits = QSerialPort::Data8;
    static const QSerialPort::StopBits stopBits = QSerialPort::OneStop;

signals:
    void remoteChanged(bool remoteEnabled);

public:
    Ohmmeter();
    ~Ohmmeter();
    bool connect(QString &portName);
    void disconnect();
    void setRemote(bool enabled);
    void setRange(int range);
    void setRate (int rate);
    void autoSetRange();
    double getCurrentReadings();
    Range getRange();
    Rate getRate();



};






#endif // OHMMETER_H
