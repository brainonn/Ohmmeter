#include "kineticsdata.h"


KineticsData::KineticsData()
{


}

void KineticsData::append(double value, int time)
{
    values.append(value);
    times.append(time);
    if(value > maxValue) maxValue = value;
    if(time > maxTime) maxTime = time;
}

double KineticsData::getMaxValue() const
{
    return maxValue;
}

int KineticsData::getMaxTime() const
{
    return maxTime;
}

int KineticsData::getLastTime() const
{
    if(times.isEmpty()) return 0;
    return times.last();
}

double KineticsData::getLastValue() const
{
    if(values.isEmpty()) return 0;
    return values.last();
}

QVector<double>& KineticsData::getValues()
{
    return values;
}

QVector<int>& KineticsData::getTimes()
{
    return times;
}

void KineticsData::clear()
{
    values.clear();
    times.clear();
    maxValue = 0;
    maxTime = 0;
}

QTextStream& operator<<(QTextStream& stream, KineticsData& data)
{
    QVector<double>::iterator itValues = data.values.begin();
    QVector<int>::iterator itTimes = data.times.begin();
    while(itValues != data.values.end()) {
        stream << *itTimes << "\t" << *itValues << "\n";
        itValues ++;
        itTimes ++;
    }
    return stream;
}
