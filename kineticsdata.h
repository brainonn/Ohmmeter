#ifndef KINETICSDATA_H
#define KINETICSDATA_H

#include <QVector>
#include <QTime>
#include <QTextStream>



class KineticsData
{
    QVector<double> values;
    QVector<double> times;
    double maxValue = 0;
    double maxTime = 0;
public:
    KineticsData();
    void append(double value, double time);
    double getMaxValue() const;
    double getMaxTime() const;
    double getLastValue() const;
    double getLastTime() const;
    QVector<double>& getValues();
    QVector<double>& getTimes();
    void clear();
    friend QTextStream& operator<<(QTextStream& stream, KineticsData& data);
};

#endif // KINETICSDATA_H
