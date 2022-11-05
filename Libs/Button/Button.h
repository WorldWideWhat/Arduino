#ifndef __BUTTON_H__
#define __BUTTON_H__
#include <Scheduler.h>
#include <DigitalInput.h>
#include <ButtonIrq.h>
#define MAX_ISR 8

namespace worldwidewhat
{
    class Button : 
        public worldwidewhat::DigitalInput, 
        public worldwidewhat::ButtonIrq, 
        public worldwidewhat::Runnable
    {

        private:
        static uint8_t _isrUsed;
        static ButtonIrq* _instance[];
        static void(* const IRAM_ATTR ISRfunc[MAX_ISR])();

        std::function<void(bool)> _callback;

        uint8_t _isrID;
        
        volatile bool _inInterrupt = false;

        bool _active = false;
        uint32_t _numberOfInterrupts = 0;
        bool _lastIrqButtonState = false;
        uint32_t _debounceTimeout = 0;
        
        uint32_t _debounceTime = 30;

        public:
        Button(const uint8_t input, bool usePullUp=true);
        bool Begin();

        void SetStateChangeCallback(std::function<void(bool)> callback);
        
        void SetDebounceTime(uint32_t debounceTime);
        const uint32_t GetDebounceTime();

        private:
        virtual void ButtonIRQ();

        private:
        virtual void Run();
        
        void StateChanged(bool state);

        static void IRAM_ATTR globalISR0(void);
        static void IRAM_ATTR globalISR1(void);
        static void IRAM_ATTR globalISR2(void);
        static void IRAM_ATTR globalISR3(void);
        static void IRAM_ATTR globalISR4(void);
        static void IRAM_ATTR globalISR5(void);
        static void IRAM_ATTR globalISR6(void);
        static void IRAM_ATTR globalISR7(void);
    };
}
#endif // __BUTTON_H__
