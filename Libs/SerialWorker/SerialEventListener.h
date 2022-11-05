/**
 * @file    SerialEventListener.h
 * @author  coder@worldwidewhat.dk
 * @date    2022-10-22
 * @version 1.0
 * @brief   Serial Event listener interface
 */
#ifndef _SERIAL_EVENT_H_
#define _SERIAL_EVENT_H_
#include <inttypes.h>

namespace worldwidewhat
{
    class SerialEventListener
    {
        public:
        virtual ~SerialEventListener() {}
        virtual void SerialDataReceived(uint8_t* data, uint32_t length);
    };
}

#endif // _SERIAL_EVENT_H_