#include <Button.h>
#include <Arduino.h>

worldwidewhat::ButtonIrq* worldwidewhat::Button::_instance[MAX_ISR];
uint8_t worldwidewhat::Button::_isrUsed = 0;

void IRAM_ATTR worldwidewhat::Button::globalISR0(void){worldwidewhat::Button::_instance[0]->ButtonIRQ();}
void IRAM_ATTR worldwidewhat::Button::globalISR1(void){worldwidewhat::Button::_instance[1]->ButtonIRQ();}
void IRAM_ATTR worldwidewhat::Button::globalISR2(void){worldwidewhat::Button::_instance[2]->ButtonIRQ();}
void IRAM_ATTR worldwidewhat::Button::globalISR3(void){worldwidewhat::Button::_instance[3]->ButtonIRQ();}
void IRAM_ATTR worldwidewhat::Button::globalISR4(void){worldwidewhat::Button::_instance[4]->ButtonIRQ();}
void IRAM_ATTR worldwidewhat::Button::globalISR5(void){worldwidewhat::Button::_instance[5]->ButtonIRQ();}
void IRAM_ATTR worldwidewhat::Button::globalISR6(void){worldwidewhat::Button::_instance[6]->ButtonIRQ();}
void IRAM_ATTR worldwidewhat::Button::globalISR7(void){worldwidewhat::Button::_instance[7]->ButtonIRQ();}

void (*const IRAM_ATTR worldwidewhat::Button::ISRfunc[MAX_ISR])()=
{
    globalISR0, globalISR1, globalISR2, globalISR3,
    globalISR4, globalISR5, globalISR6, globalISR7
};

worldwidewhat::Button::Button(const uint8_t input, bool usePullUp)
    : worldwidewhat::DigitalInput(input, usePullUp)
{
    
}

void worldwidewhat::Button::SetStateChangeCallback(std::function<void(bool)> callback)
{
    _callback = callback;
}

void worldwidewhat::Button::SetDebounceTime(uint32_t debounceTime)
{
    _debounceTime = debounceTime;
}

const uint32_t worldwidewhat::Button::GetDebounceTime()
{
    return _debounceTime;
}

bool worldwidewhat::Button::Begin()
{
    uint8_t irq = digitalPinToInterrupt(InputPin);
  
    if(irq != NOT_AN_INTERRUPT)
    {
        _isrID = UINT8_MAX;

        for(uint8_t i = 0; i < MAX_ISR;i++)
        {
            if(!(_isrUsed & _BV(i)))
            {
                _isrID = i;
                _instance[i] = this;
                _isrUsed |= _BV(i);
                break;
            }
        }
   
        if(_isrID != UINT8_MAX)
        {
            attachInterrupt(irq, ISRfunc[_isrID], CHANGE);
            worldwidewhat::Scheduler::Add(this, 50);
        }
        else
        {
            irq = NOT_AN_INTERRUPT;
        }
        
    }    
    return(irq != NOT_AN_INTERRUPT);
}

void worldwidewhat::Button::ButtonIRQ()
{    
    if(_inInterrupt) return;
    _inInterrupt = true;
    bool newState = GetState();
    _lastIrqButtonState = newState;
    _debounceTimeout = millis();
    _numberOfInterrupts++;
    _inInterrupt = false;
}

void worldwidewhat::Button::Run()
{

    bool currentState = GetState();
    _inInterrupt = true;
    uint32_t save = _numberOfInterrupts;
    bool saveDebounceTimeout = _debounceTimeout;
    bool saveLastIrqState = _lastIrqButtonState;
    _inInterrupt = false;


    if((save  != 0)
        && (currentState == saveLastIrqState)
        && (millis() - saveDebounceTimeout > _debounceTime))
    {
        StateChanged(currentState);
    }
    _inInterrupt = true;
    _numberOfInterrupts = 0;
    _inInterrupt = false;

}

void worldwidewhat::Button::StateChanged(bool state)
{
    if(_callback) _callback(state);
}