int tempPin = 1;
int val;
int redPin = 13;
int grnPin = 12;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(redPin, OUTPUT);
pinMode(grnPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
float temp = analogRead(tempPin);
temp = temp * 0.48828125;

int cel = temp;

Serial.print("Temp = ");
Serial.print(cel);
Serial.println();
delay(1000);
if (cel => 30){
  digitalWrite(redPin, HIGH);
  digitalWrite(grnPin, LOW);
  }
else{
  digitalWrite(grnPin, HIGH);
  digitalWrite(redPin, LOW);
  }

}
