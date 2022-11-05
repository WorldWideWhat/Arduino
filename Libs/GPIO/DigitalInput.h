#ifndef __DIGITAL_INPUT_H__
#define __DIGITAL_INPUT_H__
#include <Arduino.h>
#include <inttypes.h>

namespace worldwidewhat
{
    class DigitalInput
    {
        public:
        const uint8_t InputPin;
        public:
        DigitalInput(const uint8_t input, bool usePullUp=true)
            : InputPin(input)
        {
            pinMode(InputPin, usePullUp ? INPUT_PULLUP : INPUT);
        }

        bool GetState() const
        {
            return digitalRead(InputPin);
        }

    };
}

#endif // __DIGITAL_INPUT_H__