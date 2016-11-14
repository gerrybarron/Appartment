byte ledPin[] = {1,2,3,4, 5, 6, 7, 8, 9, 10, 11, 12};
int ledDelay(65); // delay between changes

int direction = 1;
int currentLED = 0;
unsigned long changeTime;
int inputPin=13;
void setup() {
  // put your setup code here, to run once:
pinMode(inputPin, INPUT);
Serial.begin(9600);
for (int x=1; x<12; x++) {
pinMode(ledPin[x], OUTPUT); }
changeTime = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
int val = digitalRead(inputPin);
Serial.println(val);
 if ((millis() - changeTime) > ledDelay) {
  changeLED();
changeTime = millis();

  }
if(val==HIGH){
   
 
  
   digitalWrite(ledPin[1], LOW);
  digitalWrite(ledPin[2], LOW);
  digitalWrite(ledPin[4], LOW);
  digitalWrite(ledPin[5], LOW);
  digitalWrite(ledPin[6], LOW);
  digitalWrite(ledPin[7], LOW);
  digitalWrite(ledPin[9], LOW);
  digitalWrite(ledPin[10], LOW);
  digitalWrite(ledPin[11], LOW);
  digitalWrite(ledPin[12], LOW);
 digitalWrite(ledPin[3], HIGH);
  digitalWrite(ledPin[8], HIGH);
}
else if (val == LOW){
 
  // digitalWrite(ledPin[1], HIGH);
  //digitalWrite(ledPin[2], HIGH);
  //digitalWrite(ledPin[4], HIGH);
  //digitalWrite(ledPin[5], HIGH);
  //digitalWrite(ledPin[6], HIGH);
  //digitalWrite(ledPin[7], HIGH);
  //digitalWrite(ledPin[9], HIGH);
  //digitalWrite(ledPin[10], HIGH);
  //digitalWrite(ledPin[11], HIGH);
  //digitalWrite(ledPin[12], HIGH);
  digitalWrite(ledPin[3], LOW);
  digitalWrite(ledPin[8], LOW);
}

}
void changeLED() {
// turn off all LED's
for (int x=1; x<12; x++) {
digitalWrite(ledPin[x], LOW);
}
digitalWrite(ledPin[currentLED], HIGH);   
currentLED += direction;
// change direction if we reach the end
if (currentLED == 11) {direction = -1;}
if (currentLED == 1) {direction = 1;}
}
  

