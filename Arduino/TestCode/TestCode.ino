#include <dht11.h>
dht11 DHT;
#define DHT11_PIN 4
int greenPin = 13;
int redPin = 12;
int buzzPin = 3;
int val;

void setup(){
  Serial.begin(9600);
  Serial.println("Type,\tStatus,\t(%),\tTemp (C),\tGas and Smoke");
  pinMode(greenPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(buzzPin, OUTPUT);
}

void loop(){
  int chk; //for checking error or status for DHT11
  Serial.print("DHT11, \t");
  chk = DHT.read(DHT11_PIN); //Read Data for DHT11
  switch (chk){
    case DHTLIB_OK:
      Serial.print("OK,\t");
      break;
    case DHTLIB_ERROR_CHECKSUM:
      Serial.print("Checksum error,\t");
      break;
    case DHTLIB_ERROR_TIMEOUT:
      Serial.print("Time out error,\t");
      break;
    default:
      Serial.print("Unknown error,\t");
      break;    
  }
  val=analogRead(0); // Read Data for Gas Value from analog 0
  // DISPLAY DATA
  Serial.print(DHT.humidity,1);
  Serial.print(",\t");
  Serial.print(DHT.temperature,1);
  Serial.print(",\t");
  Serial.println(val,DEC);
  delay(1000);
  
  if (DHT.temperature >= 33){
    digitalWrite(redPin, HIGH);
    delay(200);
    digitalWrite(redPin, LOW);
    delay(200);
    digitalWrite(greenPin, LOW);
  }
  else if (val >= 300){
    digitalWrite(redPin, HIGH);
    delay(200);
    digitalWrite(redPin, LOW);
    delay(200);
    digitalWrite(greenPin, LOW);
  }
  else if ((val >= 300) && (DHT.temperature >=33)){
    digitalWrite(redPin, HIGH);
    delay(200);
    digitalWrite(redPin, LOW);
    delay(200);
    digitalWrite(buzzPin, HIGH);
    digitalWrite(greenPin, LOW);
  }
  else {
    digitalWrite(greenPin, HIGH);
    digitalWrite(redPin, LOW);
    digitalWrite(buzzPin, LOW);
  }
 }
