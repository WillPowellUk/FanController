#pragma once
#include "mbed.h"

class FanController
{
public:
    /** Initialises the fan gpio pins and sets interrupts
    @param speedControllerPin potentiometer pin used to control the speed of the fan
    @param fanInputPin fan signal pin used as Interrupt input
    @param fanOutputPin fan signal PWM Output
    @return True if successful
    */
    FanController(const PinName& speedControllerPin, const PinName& fanInputPin, const PinName& fanOutputPin);

    /** Main run function to control speed based on potentiometer
    */
    void run();

    void setSpeed();


private:

    AnalogIn speedController;
    InterruptIn fanInterrupt;
    PwmOut fanOut;

    volatile float currentSpeed_Percentage = 0;

    /** Callback function from fanInput interrupt
    @details Updates counter until a set number have been triggered and then updates current speed
    */
    void calcCurrentSpeed();

    /** Obtains current speed from potentiometer as a percentage
    */
    float getDesiredSpeed_Percentage();


};