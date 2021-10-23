#define SENSOR_READ_DELAY 60000 // 1 minute   // 86400000 for once a day.
#define FULL_MOISTURE_READING 290
#define NO_MOISTURE_READING 595
#define CUT_OFF_MOISTURE_PERCENATGE 50
#define PUMP1_WATERING_TIME 2000  //This is millis
#define PUMP2_WATERING_TIME 2000  //This is millis
#define PUMP3_WATERING_TIME 2000  //This is millis
#define PUMP4_WATERING_TIME 2000  //This is millis

#include <SD.h>
#include <SPI.h>
#include <TimeLib.h>

File myFile;

int pinCS = 53;


int pumpPin1=2;
int pumpPin2=3;
int pumpPin3=4;
int pumpPin4=5;

int inputSensorPin1=A0;
int inputSensorPin2=A1;
int inputSensorPin3=A2;
int inputSensorPin4=A3;

void setup() 
{
  // put your setup code here, to run once:

  Serial.begin(9600);
  pinMode(pinCS, OUTPUT);
  
  // SD Card Initialization
  if (SD.begin())
  {
    Serial.println("SD card is ready to use.");
  } else
  {
    Serial.println("SD card initialization failed");
    return;
  }
  
  pinMode(pumpPin1,OUTPUT);
  pinMode(pumpPin2,OUTPUT);
  pinMode(pumpPin3,OUTPUT);
  pinMode(pumpPin4,OUTPUT);

  digitalWrite(pumpPin1,HIGH);
  digitalWrite(pumpPin2,HIGH);
  digitalWrite(pumpPin3,HIGH);
  digitalWrite(pumpPin4,HIGH);
}

void save_temperature() {
  myFile = SD.open("temp.txt", FILE_WRITE);
  myFile.print(hour());
  myFile.print(":");
  myFile.print(minute());
  myFile.print(":");
  myFile.print(day());
  myFile.print(":");
  myFile.print(month());
  myFile.print(":");
  myFile.print(year());
  myFile.print(",");
  myFile.println(int()); //save air quality data
  myFile.close();
}

void getMoisturePercentageAndWaterIt(int sensorValue, int outPinNo, int wateringTime)
{
  sensorValue = constrain(sensorValue ,FULL_MOISTURE_READING, NO_MOISTURE_READING); 
  int moisturePercentage = map(sensorValue, FULL_MOISTURE_READING, NO_MOISTURE_READING, 100, 0);
  
  if (moisturePercentage < CUT_OFF_MOISTURE_PERCENATGE)
  {
    digitalWrite(outPinNo, LOW);
    delay(wateringTime);
    digitalWrite(outPinNo, HIGH);
  }
}


void loop() 
{
  // put your main code here, to run repeatedly:

  
  // Watering
  int inputSensorPin1Value = analogRead(inputSensorPin1);
  getMoisturePercentageAndWaterIt(inputSensorPin1Value, pumpPin1, PUMP1_WATERING_TIME);

  int inputSensorPin2Value = analogRead(inputSensorPin2);
  getMoisturePercentageAndWaterIt(inputSensorPin2Value, pumpPin2, PUMP2_WATERING_TIME);

  int inputSensorPin3Value = analogRead(inputSensorPin3);
  getMoisturePercentageAndWaterIt(inputSensorPin3Value, pumpPin3, PUMP3_WATERING_TIME);

  int inputSensorPin4Value = analogRead(inputSensorPin4);
  getMoisturePercentageAndWaterIt(inputSensorPin4Value, pumpPin4, PUMP4_WATERING_TIME);

  delay(SENSOR_READ_DELAY);
}
