#include "timerhandler.h"

TimerHandler::TimerHandler(QTimer* timer)
{
    this -> timer = timer;
    if(this -> timer != nullptr && this -> timer -> isActive()) {
        this -> timer -> stop();
        flag = true;
    }

}

TimerHandler::~TimerHandler()
{
    if(flag) this -> timer -> start();
}
