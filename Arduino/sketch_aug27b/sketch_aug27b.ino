int ledPin = 13;

void setup()
{
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  for (int i=0; i<3; i++)
  {
    digitalWrite(ledPin, HIGH);
    delay(150);
    digitalWrite(ledPin, LOW);
    delay(100);
  }
  
  delay(100);
  
  for (int i=0; i<3; i++)
  {
    digitalWrite(ledPin, HIGH);
    delay(400);
    digitalWrite(ledPin, LOW);
    delay(100);
  }
  
  delay(100);
  
  for (int i=0; i<3; i++)
  {
    digitalWrite(ledPin, HIGH);
    delay(150);
    digitalWrite(ledPin, LOW);
    delay(100);
  }
  
  delay(5000);
}
