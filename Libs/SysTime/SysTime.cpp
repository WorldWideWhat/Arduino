#include "SysTime.h"

void worldwidewhat::SysTime::Take()
{
    _offset = _type == TimeType::MILLISECONDS ? millis() : micros();
}

bool worldwidewhat::SysTime::IsPassed(const uint32_t time)
{
    return ((_type == TimeType::MILLISECONDS ? millis() : micros()) - _offset) > time;
}

void worldwidewhat::SysTime::Wait(const uint32_t waitTime)
{
    Take();
    while (!IsPassed(waitTime));
}

const worldwidewhat::SysTime::TimeType worldwidewhat::SysTime::CurrentTimeType()
{
    return _type;
}