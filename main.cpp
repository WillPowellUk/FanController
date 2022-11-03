#include "mbed.h"
#include "FanController.hpp"
#include "Settings.h"

int main()
{
    FanController fan(Potentiometer_Pin, FAN_Input_Pin, FAN_PWM_Out_Pin);
    fan.run();

}

