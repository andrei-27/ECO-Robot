#define SENSOR_READ_DELAY 60000 // 1 minute   // 86400000 for once a day.
#define MIN_WATER_LEVEL 12000
#define FULL_MOISTURE_READING 290
#define NO_MOISTURE_READING 595
#define CUT_OFF_MOISTURE_PERCENATGE 101
#define PUMP1_WATERING_TIME 30000  //This is millis
#define PUMP2_WATERING_TIME 30000  //This is millis
#define PUMP3_WATERING_TIME 30000  //This is millis
#define PUMP4_WATERING_TIME 30000  //This is millis
#define PUMP5_WATERING_TIME 30000  //This is millis

#include <SD.h>
#include <SPI.h>

File myFile;

const int pinCS = 53;

const int gasSensor = A7;

const int trigPin = 41;
const int echoPin = 40;

long duration;
int distance;

const int pumpPin1=2;
const int pumpPin2=3;
const int pumpPin3=4;
const int pumpPin4=5;
const int pumpPin5=6;
const int co2Pin=7;

const int inputSensorPin1=A8;
const int inputSensorPin2=A12;
const int inputSensorPin3=A10;
const int inputSensorPin4=A11;
const int inputSensorPin5=A9;

void setup() 
{
  // put your setup code here, to run once:

  Serial.begin(9600);
  pinMode(pinCS, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
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
  pinMode(pumpPin5,OUTPUT);
  pinMode(co2Pin,OUTPUT);

  digitalWrite(pumpPin1,HIGH);
  digitalWrite(pumpPin2,HIGH);
  digitalWrite(pumpPin3,HIGH);
  digitalWrite(pumpPin4,HIGH);
  digitalWrite(pumpPin5,HIGH);
  digitalWrite(co2Pin,HIGH);
}

void getDistance() {
  for(int i = 0 ; i < 10 ; ++i)
  {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance= duration*0.034/2;
  }
  Serial.print("Distance: ");
  Serial.println(distance);
}

void saveAirQuality() {
  digitalWrite(co2Pin, LOW);
  delay(2500);
  digitalWrite(co2Pin, HIGH);
  myFile = SD.open("temp.txt", FILE_WRITE);
  float ppm;
  ppm = analogRead(gasSensor);  // read ppm value
  myFile.println(ppm); // save air quality data
  Serial.print("CO2 VALUE: ");
  Serial.print(ppm);
  Serial.println(" PPM");
  myFile.close();
}

void getMoisturePercentageAndWaterIt(int sensorValue, int outPinNo, int wateringTime)
{
  sensorValue = constrain(sensorValue ,FULL_MOISTURE_READING, NO_MOISTURE_READING); 
  int moisturePercentage = map(sensorValue, FULL_MOISTURE_READING, NO_MOISTURE_READING, 100, 0);
  
  if (moisturePercentage < CUT_OFF_MOISTURE_PERCENATGE)
  {
    Serial.print("Watering, moisture ");
    Serial.print(moisturePercentage);
    Serial.println("%");
    digitalWrite(outPinNo, LOW);
    delay(wateringTime);
    digitalWrite(outPinNo, HIGH);
  }
  else
  {
    Serial.print("Moisture level is good : ");
    Serial.print(moisturePercentage);
    Serial.println("%");
  }
}


void loop() 
{
  delay(2000);
  // put your main code here, to run repeatedly:

  getDistance();
  if(distance < MIN_WATER_LEVEL)
  {
    delay(2500);
    Serial.println("");
    // PPM read and print
    saveAirQuality();

    delay(2500);

    Serial.println("");
    // Watering
    
    int inputSensorPin1Value = analogRead(inputSensorPin1);
    getMoisturePercentageAndWaterIt(inputSensorPin1Value, pumpPin1, PUMP1_WATERING_TIME);
  
    delay(2500);
    
    int inputSensorPin2Value = analogRead(inputSensorPin1);  //stricat
    getMoisturePercentageAndWaterIt(inputSensorPin2Value, pumpPin2, PUMP2_WATERING_TIME);
  
    delay(2500);
    
    int inputSensorPin3Value = analogRead(inputSensorPin3);
    getMoisturePercentageAndWaterIt(inputSensorPin3Value, pumpPin3, PUMP3_WATERING_TIME);
    
  
    delay(2500);
    
    int inputSensorPin4Value = analogRead(inputSensorPin4);
    getMoisturePercentageAndWaterIt(inputSensorPin4Value, pumpPin4, PUMP4_WATERING_TIME);
  
    delay(2500);
  
    int inputSensorPin5Value = analogRead(inputSensorPin5);
    getMoisturePercentageAndWaterIt(inputSensorPin5Value, pumpPin5, PUMP5_WATERING_TIME);
  
    delay(2500);
   }

  else{
    Serial.println("Water level too low!");
    }

  Serial.println("");
  Serial.println("");
  delay(SENSOR_READ_DELAY);
}
