int redPin = 13;
int grnPin = 12;
int grnPin2 = 11;
int ylwPin = 10;
int buzPin = 9;

void setup() {
  // put your setup code here, to run once:
pinMode(redPin, OUTPUT);
pinMode(grnPin2, OUTPUT);
pinMode(grnPin, OUTPUT);
pinMode(ylwPin, OUTPUT);
pinMode(buzPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(redPin, HIGH);
delay(300);
digitalWrite(redPin, LOW);
digitalWrite(grnPin, HIGH);
delay(300);
digitalWrite(grnPin, LOW);
digitalWrite(grnPin2, HIGH);
delay(300);
digitalWrite(grnPin2, LOW);
digitalWrite(ylwPin, HIGH);
delay(300);
digitalWrite(ylwPin, LOW);
digitalWrite(buzPin, HIGH);
delay(300);
digitalWrite(buzPin, LOW);
delay(300);
digitalWrite(redPin, HIGH);
digitalWrite(grnPin, HIGH);
digitalWrite(grnPin2, HIGH);
digitalWrite(ylwPin, HIGH);
digitalWrite(buzPin, HIGH);
delay(300);
digitalWrite(buzPin, LOW);
digitalWrite(redPin, LOW);
digitalWrite(grnPin, LOW);
digitalWrite(grnPin2, LOW);
digitalWrite(ylwPin, LOW);
}
