#include "GoBLE.h"

#define   speedPin_M1     5//M1 speed controll
#define   speedPin_M2     6//M2 speed controll
#define   directionPin_M1 4//M1 direction controll
#define   directionPin_M2 7//M2 direction controll

//Define global variables, save the bluetooth
int joystickX, joystickY;
int buttonState[6];
bool Status = 0;

void setup() {
  pinMode(speedPin_M1, OUTPUT);
  pinMode(speedPin_M2, OUTPUT);
  pinMode(directionPin_M1, OUTPUT);
  pinMode(directionPin_M2, OUTPUT);

  digitalWrite(speedPin_M1, 0);
  digitalWrite(directionPin_M1, LOW);
  digitalWrite(speedPin_M2, 0);
  digitalWrite(directionPin_M2, LOW);

  Goble.begin();

}

void loop() {
  receive_BLE();
  if(Status == 1){
    BLEMode();
  }
}
  //controll motor 1
  void motor_M1(int speed){
    if(speed == 0){
      analogWrite(directionPin_M1, 0); //speed = 0, stop
    }
    if(speed > 0){
      digitalWrite(directionPin_M1, HIGH);//move forward
      analogWrite(speedPin_M1, speed);
    }
    else if(speed < 0){
      digitalWrite(directionPin_M1, LOW); //move backward
      analogWrite(speedPin_M1, speed);
    }
  }
  //controll motor 2
  void motor_M2(int speed){
    if(speed == 0){
      analogWrite(directionPin_M2, 0); //speed = 0, stop
    }
    if(speed > 0){
      digitalWrite(directionPin_M2, HIGH);//move forward
      analogWrite(speedPin_M2, speed);
    }
    else if(speed < 0){
      digitalWrite(directionPin_M2, LOW); //move backward
      analogWrite(speedPin_M2, speed);
    }
  }
  //motor controll
  void motorControll(int speedRight, int speedLeft){
    motor_M1(speedRight);
    motor_M2(speedLeft);
  }
  //----------------------||------------------------
  //receive bluetooth data
  void receive_BLE(){
    if(Goble.available()){
      joystickX = Goble.readJoystickX();
      joystickY = Goble.readJoystickY();
      buttonState[0] = Goble.readSwitchUp();//up 1
      buttonState[1] = Goble.readSwitchDown();//down 3
      buttonState[2] = Goble.readSwitchRight();//right 2
      buttonState[3] = Goble.readSwitchLeft();//left 4
      buttonState[4] = Goble.readSwitchSelect();//select 5
      buttonState[5] = Goble.readSwitchStart();//start 6

      if(buttonState[5] == PRESSED){
        Status = 1;
      }else {
        Status = 0;
      }
    }
  }

  //bluetooth mode
  void BLEMode(){
    if(buttonState[0] == PRESSED){
      motorControll(150, 150); //move forward
    }
    else if(buttonState[1] == PRESSED){
      motorControll(-150, -150); //move backward
    }
    else if(buttonState[2] == PRESSED){
      motorControll(-200, 200); //move right
    }
    else if(buttonState[3] == PRESSED){
      motorControll(200, -200); //move left
    }
    else {
      motorControll(0, 0); //stop
    }
  }
