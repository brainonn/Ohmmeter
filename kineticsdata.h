#ifndef KINETICSDATA_H
#define KINETICSDATA_H

#include <QVector>
#include <QTime>
#include <QTextStream>


class KineticsData
{
    QVector<double> values;
    QVector<int> times;
    double maxValue = 0;
    int maxTime = 0;
public:
    KineticsData();
    void append(double value, int time);
    double getMaxValue() const;
    int getMaxTime() const;
    double getLastValue() const;
    int getLastTime() const;
    QVector<double>& getValues();
    QVector<int>& getTimes();
    void clear();
    friend QTextStream& operator<<(QTextStream& stream, KineticsData& data);
};

#endif // KINETICSDATA_H
