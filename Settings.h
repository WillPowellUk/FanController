#pragma once 
#include <cstdint>

/* GPIO Hardware Pins */
// Fan Pins
#define Potentiometer_Pin D8
#define FAN_Input_Pin D14
#define FAN_PWM_Out_Pin D15

// SD Card SPI pins
#define SD_MOSI D11
#define SD_MISO D12
#define SD_SCK D13
#define SD_CS D10

// FAN PWM 
#define PWM_0 D9

#define SerialPrint

namespace Settings 
{

    namespace Audio
    {
        const constexpr unsigned short SampleRate_Hz = 22050;
        const constexpr uint8_t SampleSize_bits = 16;
    }

    namespace Fan
    {
        /* HARDWARE PARAMETERS */
        // number of encodings (i.e. # of rising/falling signals) per revolution of the fan
        const constexpr uint8_t NumOfEncodingsPerRev = 4;
        // Encoding triggered on Rising edge if true, otherwise on falling edge
        const constexpr bool RisingEncoding = true;
        // Maximum speed of fan in RPM
        const constexpr uint16_t MaxSpeed_RPM = 500;

        /*  TUNING PARAMETERS */
        // waits for this number of encodings before updating the current speed
        const constexpr uint16_t NumOfEncodingsForCurrentSpeed = 10;

        const constexpr float kp = 1.0;
        const constexpr float ki = 1.0;
        const constexpr float kd = 1.0;

    }


}
