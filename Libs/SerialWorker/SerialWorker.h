#ifndef _SERIAL_WORKER_H_
#define _SERIAL_WORKER_H_

#include <vector>
#include <inttypes.h>
#include <Runnable.h>
#include <Scheduler.h>
#include <SerialEventListener.h>

namespace worldwidewhat
{
    class SerialWorker : Runnable
    {
        private:
        std::vector<SerialEventListener*> _eventsListeners;

        public:
        SerialWorker(uint32_t pollInterval=1)
        {
            if(pollInterval < 1) pollInterval = 1;
            Scheduler::GetInstance().Add(this, 1);
        }

        static SerialWorker &GetInstance();

        void AddListener(SerialEventListener *listener);

        virtual void Run();

    };
}

#endif // _SERIAL_WORKER_H_