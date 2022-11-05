/**
 * @file    SchedulerItem.h
 * @author  coder@worldwidewhat.dk
 * @date    2022-10-22
 * @version 1.0
 * @brief   System scheduler item
  */
#ifndef __WORLDWIDEWHAT__SCHEDULER_ITEM_H__
#define __WORLDWIDEWHAT__SCHEDULER_ITEM_H__

#include <Runnable.h>
#include <SysTime.h>

namespace worldwidewhat
{
    class SchedulerItem
    {
        private:
        Runnable * _runnable;
        uint32_t _interval;
        SysTime _sysTime;

        public:
        SchedulerItem(Runnable *runable, uint32_t interval) 
            : _runnable(runable), _interval(interval)
        {
            _sysTime.Take();
        }

        Runnable *getRunnable()
        {
            return _runnable;
        }

        void Execute()
        {
            if(_sysTime.IsPassed(_interval))
            {
                _runnable->Run();
                _sysTime.Take();
            }
        }
    };
}

#endif // __WORLDWIDEWHAT__SCHEDULER_ITEM_H__