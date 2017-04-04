#ifndef OHMMETER_H
#define OHMMETER_H

#include <QSerialPort>
#include <QTimer>


enum Range {r20m = 1, r200m, r2, r20, r200, r2k, r20k, r200k, r2M};
enum Rate {fast, slow};
const int firstWaitTime = 50;
const int additionalWaitTime = 5;
const int updateInterval = 100;
struct Readings {
    double value = 0;
    QString units = "mOhm";
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
    Readings currentReadings;

signals:
    void remoteChanged(bool remoteEnabled);
    void readingsChanged(Readings readings);
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
    Range getRange();
    Rate getRate();
    QString getResponse();
    Readings parseReadingsString(const QString& str);




};








#endif // OHMMETER_H
