#include <math.h> // Used for calculations 
int TempPIN = A0;// Analog Pin 0 for temperature
int pHPIN = A2; // Analog Pin 2 for pH sensor
int TimeInterval = 500; // Time between readings (in ms)
int InputNumber = 0;

void setup() 
{
  Serial.begin(9600);
}
void loop() 
{
  int count; //reading from the A/D converter (10-bit)
  float temp; //the print below does the division first to avoid overflows
  count = analogRead(TempPIN); // read count from the A/D converter 
  temp = thermistor(count); // and  convert it to CelsiusSerial.print(Time/1000); //display in seconds, not milliseconds                       
  Serial.print(temp,1); // display temperature to one digit  
  Serial.print(" , ");
  float voltage, pH; //global variable for reading from A/D converter
  voltage = getVoltage(pHPIN); //Measure the voltage at the analog pin
  pH = ((1.75 - voltage) / .25) + 7 ; // Convert the voltage to pH levels
  Serial.println(pH);                              
  delay(TimeInterval); // Delay a bit... 
  InputNumber++;  
}
float thermistor(int raw) //This function calculates temperature from ADC count
{
  
  long resistance; 
  float resistor = 15000; //fixed resistor 
  float temp;  // Dual-Purpose variable to save space.
  resistance=( resistor*raw /(1024-raw)); 
  temp = log(resistance); // Saving the Log(resistance) to not calculate it 4 times later
  temp = 1 / (0.00102119 + (0.000222468 * temp) + (0.000000133342 * temp * temp * temp));
  temp = temp - 273.15; // Convert Kelvin to Celsius   
  temp = (temp * 9.0)/ 5.0 + 32.0; //Convert Celsius to Fahrenheit                     
  return temp; // Return the Temperature
}
float getVoltage(int pin)   
{
  return (analogRead(pin) * 0.004882814); //calculate and return pH value from raw voltage data
}
