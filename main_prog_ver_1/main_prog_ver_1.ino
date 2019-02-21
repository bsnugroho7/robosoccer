#define   speedPin_M1     5//M1 speed controll
#define   speedPin_M2     6//M2 speed controll
#define   directionPin_M1 4//M1 direction controll
#define   directionPin_M2 7//M2 direction controll

//Define global variables, save the bluetooth
int input;
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
    if(Serial.available()){
      input = Serial.read();
      switch(input){
        Status=1;
        case '0': buttonState[0] = input; break; 
        case '1': buttonState[1] = input; break; 
        case '2': buttonState[2] = input; break; 
        case '3': buttonState[3] = input; break; 
//        case '4': Status = 1; break;
//        case '5': Status = 0; break;
      }
    }
  }

  //bluetooth mode
  void BLEMode(){
    if(buttonState[0] == 0){
      motorControll(150, 150); //move forward
    }
    else if(buttonState[1] == 1){
      motorControll(-150, -150); //move backward
    }
    else if(buttonState[2] == 2){
      motorControll(-200, 200); //move right
    }
    else if(buttonState[3] == 3){
      motorControll(200, -200); //move left
    }
    else {
      motorControll(0, 0); //stop
    }
  }
