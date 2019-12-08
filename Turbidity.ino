#include <EEPROM.h> // libarary that acts as a memory whose values are kept when the board is turned off (like a tiny hard drive). This library enables you to read and write those bytes.
int input = 0; // Analog sensor value (0-1023)
int sensor_samp = 0; // Averaging variable, sums samples
int n = 10; // Number of samples to average
float voltage = 0.00; // Voltage value derived from analog output (~0-4.5V)
// float Vclear = 4.240; // Calibration variable; voltage at ~0 NTU
// float rel_turb = 00.00; // Relative turbidity value, based on comparison of measured voltage with Vclear

void setup()
{
  Serial.begin(9600); // Baud rate: 9600 bps
  // EEPROM.get(0,Vclear); // Retrieve previous Vclear calibration value
}
void loop()
{
  for (int i=0; i < n; i++)
      {
      sensor_samp += analogRead(A0); // read the input on analog pin 0 (turbidity sensor analog output) 
      delay(10);
      }
  input = sensor_samp / n; // Averages n samples
  voltage = input * (5.000 / 1023.000); // Convert the analog reading (0 - 1023) to a voltage (~0 - 4.5)
  // rel_turb = 100.00 - (voltage/Vclear)*100.00; // Relative percentage, 0% = ideal clear water
  Serial.println(voltage); // Print out the value
  sensor_samp = 0;
  delay(500); // Repeat every 500ms
}
