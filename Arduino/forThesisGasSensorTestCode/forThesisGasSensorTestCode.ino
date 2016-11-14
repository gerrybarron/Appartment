int smkPin = 0;
///Arduino Sample Code
void setup()
{
  
  Serial.begin(9600); //Set serial baud rate to 9600 bps
}
void loop()
{
int smokeVal = analogRead(smkPin);//Read Gas value from analog 0
Serial.println(smokeVal);//Print the value to serial port
delay(100);
}
