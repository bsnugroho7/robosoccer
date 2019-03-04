#define   speedPin_M1     5//M1 speed controll
#define   speedPin_M2     6//M2 speed controll
#define   directionPin_M1 4//M1 direction controll
#define   directionPin_M2 7//M2 direction controll
#define   LED_PWM1        11//LED PWM1
#define   LED_PWM2        12//LED PWM2

//Define global variables, save the bluetooth
int input;
bool buttonState[5];
bool Status = 0;

void setup() {
  pinMode(speedPin_M1, OUTPUT);
  pinMode(speedPin_M2, OUTPUT);
  pinMode(directionPin_M1, OUTPUT);
  pinMode(directionPin_M2, OUTPUT);
  pinMode(LED_PWM1, OUTPUT);
  pinMode(LED_PWM2, OUTPUT);

  digitalWrite(LED_PWM1, LOW);
  digitalWrite(LED_PWM2, LOW);
  digitalWrite(speedPin_M1, 0);
  digitalWrite(directionPin_M1, LOW);
  digitalWrite(speedPin_M2, 0);
  digitalWrite(directionPin_M2, LOW);

  Serial.begin(9600);
}

void loop() {
  receive_BLE();
  if(Status == 1){
    BLEMode();
  }
}
  //controll motor 1
  void motor_M1(int speed){
    if(speed == 255){
      analogWrite(directionPin_M1, speed); //speed = 0, stop
      digitalWrite(LED_PWM1, LOW);//Indicator Motor1 Off
    }
    if(speed >= 0){
      digitalWrite(directionPin_M1, HIGH);//move forward
      digitalWrite(LED_PWM1, HIGH);//Indicator Motor1 On
      analogWrite(speedPin_M1, speed);
    }
    else if(speed < 0){
      digitalWrite(directionPin_M1, LOW); //move backward
      digitalWrite(LED_PWM1, HIGH);//Indicator Motor1 On
      analogWrite(speedPin_M1, speed);
    }
  }
  //controll motor 2
  void motor_M2(int speed){
    if(speed == 255){
      analogWrite(directionPin_M2, speed); //speed = 0, stop
      digitalWrite(LED_PWM2, LOW);//Indicator Motor2 Off
    }
    if(speed >= 0){
      digitalWrite(directionPin_M2, HIGH);//move forward
      digitalWrite(LED_PWM2, HIGH);//Indicator Motor2 On
      analogWrite(speedPin_M2, speed);
    }
    else if(speed < 0){
      digitalWrite(directionPin_M2, LOW); //move backward
      digitalWrite(LED_PWM2, HIGH);//Indicator Motor2 On
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
      Status = 1;
      switch(input){
        case '0': buttonState[0] = true; 
        buttonState[1] = false;
        buttonState[2] = false;
        buttonState[3] = false;
        buttonState[4] = false;break;
        case '1': buttonState[1] = true; 
        buttonState[0] = false;
        buttonState[2] = false;
        buttonState[3] = false;
        buttonState[4] = false;break;
        case '2': buttonState[2] = true; 
        buttonState[0] = false;
        buttonState[1] = false;
        buttonState[3] = false;
        buttonState[4] = false;break; 
        case '3': buttonState[3] = true; 
        buttonState[0] = false;
        buttonState[1] = false;
        buttonState[2] = false;
        buttonState[4] = false;break; 
        case '4': buttonState[4] = true; 
        buttonState[0] = false;
        buttonState[1] = false;
        buttonState[2] = false;
        buttonState[3] = false;break; 
      }
    } 
  }

  //bluetooth mode
  void BLEMode(){
    
    if(buttonState[1] == true){
      motorControll(0, 0); //move forward
      Serial.println("Maju");
    }
    else if(buttonState[2] == true){
      motorControll(-50, -50); //move backward
      Serial.println("Mundur");
    }
    else if(buttonState[3] == true){
      motorControll(175, -175); //move right
      Serial.println("Kanan");
    }
    else if(buttonState[4] == true){
      motorControll(-175, 175); //move left
      Serial.println("Kiri");
    }
    else if(buttonState[0] == true){
      motorControll(255, 255); //stop
      Serial.println("Stop");
    }
  }
