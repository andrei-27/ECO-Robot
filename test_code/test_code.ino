
const int pumpPin1=2;
const int pumpPin2=3;
const int pumpPin3=4;
const int pumpPin4=5;
const int pumpPin5=6;

void setup() 
{
  // put your setup code here, to run once:

  Serial.begin(9600);
 
  
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




void loop() 
{
  Serial.print("Watering, moisture ");
  Serial.println("%");
  digitalWrite(pumpPin1, LOW);
  delay(10000);
  digitalWrite(pumpPin1, HIGH);
  delay(2000);
  
  Serial.print("Watering, moisture ");
  Serial.println("%");
  digitalWrite(pumpPin2, LOW);
  delay(5000);
  digitalWrite(pumpPin2, HIGH);
  delay(2000);
  
  Serial.print("Watering, moisture ");
  Serial.println("%");
  digitalWrite(pumpPin3, LOW);
  delay(10000);
  digitalWrite(pumpPin3, HIGH);
  delay(2000);
  
  Serial.print("Watering, moisture ");
  Serial.println("%");
  digitalWrite(pumpPin4, LOW);
  delay(10000);
  digitalWrite(pumpPin4, HIGH);
  delay(2000);
  
  Serial.print("Watering, moisture ");
  Serial.println("%");
  digitalWrite(pumpPin5, LOW);
  delay(10000);
  digitalWrite(pumpPin5, HIGH);
  delay(2000);

  Serial.print("END");
}
