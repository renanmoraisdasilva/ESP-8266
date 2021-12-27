# ESP-8266
An application of the NodeMCU ESP-8266 to sample a signal, calculate the RMS value and output a PWM Signal with the related duty-cycle.

I would like to thank OverEngineeredInOz for his amazing work regarding fast-sampling using Arduino, which was was of great help, check him out at: https://github.com/OverEngineeredInOz

This Arduino program is intended to be used with NodeMCU ESP-8266 and is part of my final project in Mechanical Engineering undergraduate course.

The main objective is to read and interpret a wave function and output a PWM signal. The intended use is to read a wave function produced by the Hall Effect-Based Linear Current Sensor ACS712 - 5A when connected in series with a electrical load, such as a lamp, it converts a electrical current into a proportional voltage with a sensitivity of 0.185V/A and offset of 2.5V. That enables us to read the voltage using the single Analog input port in the ESP-8266.

As part of the code there is a setup, calibration, getcurrent and a loop functions. 

The setup function:
- Initializes the serial communication
- Calls the calibration function and stores the result of the offset in the "zero" variable.
- Sets the ESP's analog write resolution to 10 bits.
- Sets the ESP's PWM write frequency to 200Hz.
- Sets the built-in LED as output.

The calibration function:
- Samples 1000 voltage readings
- Calculates the simple average of the samples, prints and returns it.

The getcurrent function:
- Calculates the RMS value of the 800-point voltage sample. It does so applying the definition of the root mean square (RMS) by adding all of the square values and then taking the average and applying the square root.
- Note that, first, the value recorded is in a range of 0-1023 which is the resolution of ESP's ADC, so it first needs to be converted to volts by multiplying by 3 and dividing by 1023, then to get the related current value it is devided by 0.185.

The loop function:
- Samples the value of the wave 800 times with a average frequency of about 20kHz and stores in the sampleValue array.
- Records the timestamp of each reading in the sampleTime array.
- Calculates the average sampling rate by getting the total time it takes for the 800 samples to be recorded and divides by the number of samples.
- Calls the getcurrent function and stores the result in currentRMS variable
- Calculates the power by multiplying the current by 220V.
- Generates a PWM wave with duty cycle 0-100%, which translates to 0-100W.
- Delays 500ms.
