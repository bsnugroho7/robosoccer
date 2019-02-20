#include <Servo.h>
#include <Metro.h>
#include "GoBLE.h"
#include <Wire.h>

#define     CAR_TYPE         1//1:car type cherokry

#define     speedPin_M1      5//M1 speed control  
#define     speedPin_M2      6//M2 speed control
#define     directionPin_M1  4//M1 direction control
#define     directionPin_M2  7//M2 direction control
#define     URPWM            3 //ultrosonic module（0－25000US，50US is 1cm）
#define     URTRIG           10 //ultrosonic trig pin  
#define     SERVO_PIN        9

Metro measureDistance = Metro(50);//build metro object, the interval is 50ms
Metro sweepServo = Metro(20);//build metro object, the interval is 20ms

unsigned long actualDistance = 0;

Servo myservo;//build the servo 
int pos = 90;
int sweepFlag = 1;

//Define global variables, save the bluetooth data
int joystickX, joystickY;
int buttonState[6];
bool mode = 0; //mode=0：avoid obstacle, mode=1：control by bluetooth

void setup() {
  pinMode(speedPin_M1, OUTPUT);
  pinMode(speedPin_M2, OUTPUT);
  pinMode(directionPin_M1, OUTPUT);
  pinMode(directionPin_M2, OUTPUT);

  digitalWrite(speedPin_M2, 0);
  digitalWrite(directionPin_M2, LOW);
  digitalWrite(speedPin_M1, 0);
  digitalWrite(directionPin_M1, LOW);

  pinMode(URTRIG, OUTPUT);
  digitalWrite(URTRIG, HIGH);
  pinMode(URPWM, INPUT);

  Goble.begin();
  myservo.attach(SERVO_PIN);
  myservo.write(pos);
  Serial.begin(115200);
  delay(1000);
  Serial.println("setup");
}

void loop() {
  receive_BLE();
  if (mode == 1) {
    BLEMode();//Bluetooth mode
  } else {
    avoidanceMode();//avoid obstacle mode
  }
}
//control motor 1
void motorM1Control(int speed) {
  if (speed == 0) {
    analogWrite(speedPin_M1, 0); //speed = 0, stop
  }
  if (CAR_TYPE == 1) {
    if (speed > 0) {
      digitalWrite(directionPin_M1, HIGH); //direction pin set low, move forward
      analogWrite(speedPin_M1, speed);
    } else if (speed < 0) {
      digitalWrite(directionPin_M1, LOW); //direction pin set high, move backward
      analogWrite(speedPin_M1, -speed);
    }
  } else if (CAR_TYPE == 2 || CAR_TYPE == 3) {
    if (speed > 0) {
      digitalWrite(directionPin_M1, LOW); //direction pin set low, move forward
      analogWrite(speedPin_M1, speed);
    }
    else if (speed < 0) { //否则
      digitalWrite(directionPin_M1, HIGH); //direction pin set high, move backward
      analogWrite(speedPin_M1, -speed);
    }
  }
}
//电机M2控制
void motorM2Control(int speed) {
  if (speed == 0) {
    analogWrite(speedPin_M2, 0); //speed = 0, stop
  }
  if (CAR_TYPE == 1) {
    if (speed > 0) {
      digitalWrite(directionPin_M2, LOW); //direction pin set low, move forward
      analogWrite(speedPin_M2, speed);
    }
    else if (speed < 0) {
      digitalWrite(directionPin_M2, HIGH); //direction pin set high, move backward
      analogWrite(speedPin_M2, -speed);
    }
  } else if (CAR_TYPE == 2 || CAR_TYPE == 3) {
    if (speed > 0) {
      digitalWrite(directionPin_M2, LOW); //direction pin set low, move forward
      analogWrite(speedPin_M2, speed);
    }
    else if (speed < 0) {
      digitalWrite(directionPin_M2, HIGH); //direction pin set high, move backward
      analogWrite(speedPin_M2, -speed);
    }
  }
}
//motor control
void motorControl(int speedRight, int speedLeft ) {
  motorM1Control(speedRight);
  motorM2Control(speedLeft);
}

int MeasureDistance() {
  digitalWrite(URTRIG, LOW);//URTRIG set low
  digitalWrite(URTRIG, HIGH);//PWM mode trig
  unsigned long distance = pulseIn(URPWM, LOW); //read PWM
  if (distance >= 30000) {
    Serial.println("Invalid");//read invalid
  } else {
    distance = distance / 50; //50us means 1cm
  }
  if (distance > 4) {
    return distance;//filter distance less than 4
  }
}
//servo control
void servoSweep() {
  if (sweepFlag) {
    if (pos >= 60 && pos <= 120) {
      pos = pos + 10;
      myservo.write(pos);
    }
    if (pos > 119)  sweepFlag = false;
  }
  else {
    if (pos >= 60 && pos <= 120) {
      pos = pos - 10;
      myservo.write(pos);
    }
    if (pos < 61)  sweepFlag = true;
  }
}
//receive bluetooth data
void receive_BLE()
{
  if (Goble.available()) {
    joystickX = Goble.readJoystickX();
    joystickY = Goble.readJoystickY();
    buttonState[0]     = Goble.readSwitchUp();//up 1
    buttonState[1]   = Goble.readSwitchDown();//down 3
    buttonState[2]   = Goble.readSwitchLeft();//left 4
    buttonState[3]  = Goble.readSwitchRight();//rght 2
    buttonState[4] = Goble.readSwitchSelect();//select 5
    buttonState[5]  = Goble.readSwitchStart();//start 6
    if (buttonState[4] == PRESSED) {
      mode = 1;// if SWITCH_SELECT pressed，mode=1，switch to bluetooth mode
    }
    if (buttonState[5] == PRESSED) {
      mode = 0;//if SWITCH_START pressed，mode=0，switch to avoid obstacle mode
    }
  }
}

void BLE_Delay(int Time)
{
  for (int i = Time; i > 0; i--) {
    delay(1);//delay and receive bluetooth data, when received, stop delay
    if (Goble.available()) {
      joystickX = Goble.readJoystickX();
      joystickY = Goble.readJoystickY();
      buttonState[0]     = Goble.readSwitchUp();
      buttonState[1]   = Goble.readSwitchDown();
      buttonState[2]   = Goble.readSwitchLeft();
      buttonState[3]  = Goble.readSwitchRight();
      buttonState[4] = Goble.readSwitchSelect();
      buttonState[5]  = Goble.readSwitchStart();
      if (buttonState[4] == PRESSED) {
        mode = 1;//if SWITCH_SELECT pressed，mode=1，switch to bluetooth mode
        break;
      }
    }
  }
}
//avoid obstacle mode
void avoidanceMode() {
  if (measureDistance.check() == 1) {
    actualDistance = MeasureDistance();//measure distance
    Serial.println(actualDistance);
  }
  if (sweepServo.check() == 1) {
    servoSweep();//servo control
  }
  if (actualDistance <= 30) {
    myservo.write(90);
    if (pos >= 90) {
      motorControl(0, 0);
      BLE_Delay(500);
      motorControl(-200, -200); //move back
      BLE_Delay(500);
      motorControl(-200, 200); //turn right
      BLE_Delay(500);
    } else {
      motorControl(0, 0);
      BLE_Delay(500);
      motorControl(-200, -200); //move back
      BLE_Delay(500);
      motorControl(200, -200); //turn left
      BLE_Delay(500);
    }
  } else {
    motorControl(150, 150); //move forward
    BLE_Delay(300);
  }
}
//bluetooth mode
void BLEMode() {
  if (buttonState[0] == PRESSED) {
    motorControl(150, 150); //move forward
  }
  else if (buttonState[1] == PRESSED) {
    motorControl(-150, -150); //move back
  }
  else if (buttonState[2] == PRESSED) {
    motorControl(200, -200); //turn left
  }
  else if (buttonState[3] == PRESSED) {
    motorControl(-200, 200); //turn right
  }
  else {
    motorControl(0, 0); //stop
  }
}
