#ifndef TIMERHANDLER_H
#define TIMERHANDLER_H
#include <QTimer>

class TimerHandler
{
    QTimer* timer;
    bool flag = false;
public:
    TimerHandler(QTimer* timer);
    ~TimerHandler();
};

#endif // TIMERHANDLER_H
