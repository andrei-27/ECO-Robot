#include <avr/sleep.h>

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.println("Program is on");
  Serial.flush ();
  sleepNow();
}

void sleepNow()
{
  // Choose our preferred sleep mode:
  set_sleep_mode(SLEEP_MODE_PWR_SAVE);
  // Set sleep enable (SE) bit:
  sleep_enable();
  // Put the device to sleep:
  sleep_mode();
  // Upon waking up, sketch continues from this point.
  sleep_disable();

  int sensorValue = analogRead(0); // Read analog input pin A0
  Serial.println(sensorValue, DEC); // Print the value read
}
