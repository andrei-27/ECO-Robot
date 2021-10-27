
const int inputSensorPin1=A8;
const int inputSensorPin2=A9;
const int inputSensorPin3=A10;
const int inputSensorPin4=A11;
const int inputSensorPin5=A12;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  /*
  for(int i = 0 ; i<20 ; i++)
  {Serial.println(analogRead(inputSensorPin1));
  delay(500);}
  Serial.println("");
  
  for(int i = 0 ; i<20 ; i++)
  {Serial.println(analogRead(inputSensorPin2));
  delay(500);}
  Serial.println("");
  
  for(int i = 0 ; i<20 ; i++)
  {Serial.println(analogRead(inputSensorPin3));
  delay(500);}
  Serial.println("");
  
  for(int i = 0 ; i<20 ; i++)
  {Serial.println(analogRead(inputSensorPin4));
  delay(500);}
  Serial.println("");
  */
  
  for(int i = 0 ; i<20 ; i++)
  {Serial.println(analogRead(inputSensorPin5));
  delay(500);}
  //Serial.println("");
}
