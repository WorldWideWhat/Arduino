#include <SerialWorker.h>

static worldwidewhat::SerialWorker _private_static_serialworker(1);

worldwidewhat::SerialWorker &worldwidewhat::SerialWorker::GetInstance()
{
    return _private_static_serialworker;
}

void worldwidewhat::SerialWorker::AddListener(SerialEventListener *listener)
{
    GetInstance()._eventsListeners.push_back(listener);
}

void worldwidewhat::SerialWorker::Run()
{
    if(!Serial.available()) return;
    uint8_t *buffer;
    uint32_t size = Serial.available();
    buffer = (uint8_t*)malloc(size);
    Serial.readBytes(buffer, size);

    for(uint32_t listernerIndex = 0; listernerIndex < _eventsListeners.size(); listernerIndex++)
    {
        _eventsListeners[listernerIndex]->SerialDataReceived(buffer, size);
    }
}
