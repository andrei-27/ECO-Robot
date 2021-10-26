#define SENSOR_READ_DELAY 10000 // 1 minute   // 86400000 for once a day.
#define MIN_WATER_LEVEL 12
#define FULL_MOISTURE_READING 290
#define NO_MOISTURE_READING 595
#define CUT_OFF_MOISTURE_PERCENATGE 50
#define PUMP1_WATERING_TIME 2000  //This is millis
#define PUMP2_WATERING_TIME 2000  //This is millis
#define PUMP3_WATERING_TIME 2000  //This is millis
#define PUMP4_WATERING_TIME 2000  //This is millis
#define PUMP5_WATERING_TIME 2000  //This is millis

#include <SD.h>
#include <SPI.h>

File myFile;

const int pinCS = 53;

const int gasSensor = A0;

const int trigPin = 30;
const int echoPin = 31;

long duration;
int distance;

int pumpPin1=2;
int pumpPin2=3;
int pumpPin3=4;
int pumpPin4=5;
int pumpPin5=6;

int inputSensorPin1=A8;
int inputSensorPin2=A9;
int inputSensorPin3=A10;
int inputSensorPin4=A11;
int inputSensorPin5=A12;

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

  digitalWrite(pumpPin1,HIGH);
  digitalWrite(pumpPin2,HIGH);
  digitalWrite(pumpPin3,HIGH);
  digitalWrite(pumpPin4,HIGH);
  digitalWrite(pumpPin5,HIGH);
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
  delay(4000);
  // put your main code here, to run repeatedly:

  getDistance();
  if(distance < MIN_WATER_LEVEL)
  {
    Serial.println("");
    // PPM read and print
    saveAirQuality();

    Serial.println("");
    // Watering
    int inputSensorPin1Value = analogRead(inputSensorPin1);
    getMoisturePercentageAndWaterIt(inputSensorPin1Value, pumpPin1, PUMP1_WATERING_TIME);
  
    delay(1000);
    
    int inputSensorPin2Value = analogRead(inputSensorPin2);
    getMoisturePercentageAndWaterIt(inputSensorPin2Value, pumpPin2, PUMP2_WATERING_TIME);
  
    delay(1000);
    
    int inputSensorPin3Value = analogRead(inputSensorPin3);
    getMoisturePercentageAndWaterIt(inputSensorPin3Value, pumpPin3, PUMP3_WATERING_TIME);
  
    delay(1000);
    
    int inputSensorPin4Value = analogRead(inputSensorPin4);
    getMoisturePercentageAndWaterIt(inputSensorPin4Value, pumpPin4, PUMP4_WATERING_TIME);
  
    delay(1000);
  
    int inputSensorPin5Value = analogRead(inputSensorPin5);
    getMoisturePercentageAndWaterIt(inputSensorPin5Value, pumpPin5, PUMP5_WATERING_TIME);
  
    delay(1000);
   }

  else{
    Serial.println("Water level too low!");
    }

  Serial.println("");
  Serial.println("");
  delay(SENSOR_READ_DELAY);
}
