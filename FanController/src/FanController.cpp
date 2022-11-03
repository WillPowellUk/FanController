#include "FanController.hpp"
#include "Settings.h"

FanController::FanController(const PinName& speedControllerPin, const PinName& fanInputPin, const PinName& fanOutputPin)
    : speedController(speedControllerPin)
    , fanInterrupt(fanInputPin)
    , fanOut(fanOutputPin)
{
    // attach callback function calcFanSpeed on rising edge
    if (Settings::Fan::RisingEncoding) fanInterrupt.rise(callback(this, &FanController::calcCurrentSpeed));
    else fanInterrupt.fall(callback(this, &FanController::calcCurrentSpeed));
}

void FanController::calcCurrentSpeed()
{
    static volatile uint16_t encodingCounter = 0;
    static volatile uint32_t previousTime = 0;

    // increment encoding counter and update current speed if number of encodings have been reached
    if(++encodingCounter >= Settings::Fan::NumOfEncodingsForCurrentSpeed)
    {
        // calculate number of revolutions
        uint16_t revolutions = encodingCounter / Settings::Fan::NumOfEncodingsPerRev;
        // reset counter
        encodingCounter = 0;

        // calculate time taken in minutes.
        double timeTaken_min = (us_ticker_read() - previousTime) / 60e6;
        // reset time
        previousTime = us_ticker_read();

        // update current speed (as a percentage of maximum speed)
        currentSpeed_Percentage =  (revolutions / timeTaken_min) / Settings::Fan::MaxSpeed_RPM;
    }
}


float FanController::getDesiredSpeed_Percentage()
{
    return speedController.read(); 
}



void FanController::run()
{
    while(true)
    {
        // error is difference between desired speed and actual speed
        float error = getDesiredSpeed_Percentage() - currentSpeed_Percentage;
        
        /* PWM Fan Output Calculated from PID */
        static uint32_t previousTime = 0;
        static uint32_t previousError = 0;
        static float integralError = 0;

        // calculate time time elapsed
        uint32_t currentTime = us_ticker_read();
        uint32_t timeElapsed = currentTime - previousTime;
        previousTime = currentTime;

        // calculate cumaltive error
        integralError += error * timeElapsed;

        // calculate change in error
        float derivativeError = (error - previousError)/timeElapsed;
        previousError = error;

        float PWM_Output = Settings::Fan::kp * (error + (Settings::Fan::ki * integralError) + (Settings::Fan::kd * derivativeError));

        if(PWM_Output > 1.0) PWM_Output = 1.0;
        else if (PWM_Output < 0.0) PWM_Output = 0.0;
        fanOut.write(PWM_Output);

    }
    

}



