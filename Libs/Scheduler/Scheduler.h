#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_

#include <vector>
#include <inttypes.h>
#include <Runnable.h>
#include <SchedulerItem.h>

namespace worldwidewhat
{
    class Scheduler
    {
        private:
        std::vector<SchedulerItem> _runnables;
        //List<SchedulerItem> _runnables;

        public:

        static Scheduler &GetInstance();

        static void Add(Runnable *runnable, uint32_t interval);
        void Run();

        private:
        void ExecuteItems();
    };
}

#endif // _SCHEDULER_H_