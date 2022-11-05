#include <Scheduler.h>
#define SCHEDULER_LOOP_DELAY 0 // Delay between each loop. Set to zero if no delay


 worldwidewhat::Scheduler &worldwidewhat::Scheduler::GetInstance()
 {
    static worldwidewhat::Scheduler scheduler;
    return scheduler;
 }

void worldwidewhat::Scheduler::Run()
{

    static SysTime timer;
    if(timer.IsPassed(SCHEDULER_LOOP_DELAY))
    {
        ExecuteItems();
        timer.Take();
    }
}

void worldwidewhat::Scheduler::Add(Runnable *runnable, uint32_t interval)
{
    SchedulerItem item(runnable, interval);
    GetInstance()._runnables.push_back(item);
    //GetInstance()._runnables.Add(item);
}

void worldwidewhat::Scheduler::ExecuteItems()
{
    for(uint32_t index = 0; index < _runnables.size(); index++)
    {
        _runnables[index].Execute();
    }
}
