#include <Servo.h>
Servo myservo;
int pos;
int input;
bool status = 0;
void setup() {
  myservo.attach(9); // objek servo diletakkan pada pin 9
  myservo.write(45);
  input = 0;
  Serial.begin(9600);
}

void loop() {
  // Start servo dari 0 derajat sampai 90 derajat
  if(Serial.available()){
    input = Serial.read();
    if(input == '1'){
      Serial.println("Kicker on");
      myservo.write(150);
    }
    else if(input == '0'){
      Serial.println("Kicker off");
      myservo.write(45);
    }
  }
}
    
  
  // Balikin servo dari 90 derajat ke 0 derajat
  //for(pos = 150; pos >= 90; pos -= 1){
    //myservo.write(pos);
    //delay(5);
  //}
