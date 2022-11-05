/**
 * @file    SysTime.h
 * @author  coder@worldwidewhat.dk
 * @date    2022-10-22
 * @version 1.0
 * @brief   System time usage
 */

#ifndef _SYSTIME_H_
#define _SYSTIME_H_
#include <Arduino.h>
#include <inttypes.h>

namespace worldwidewhat
{
    class SysTime
    {
        public:
        enum class TimeType
        {
            MILLISECONDS = 0,
            MICROSECONDS = 1
        };

        private:
        TimeType _type;
        uint64_t _offset;

        public:
        SysTime(TimeType type = TimeType::MILLISECONDS) :
            _type(type), 
            _offset((type == TimeType::MILLISECONDS) ? millis() : micros())
            {}

        void Take();
        
        bool IsPassed(const uint32_t time);

        void Wait(const uint32_t waitTime);

        const TimeType CurrentTimeType();
    };
}

#endif /* _SYSTIME_H_ */