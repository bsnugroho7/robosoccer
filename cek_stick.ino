 #include <PS2X_lib.h>



PS2X ps2x; // create PS2 Controller Class


//right now, the library does NOT support hot pluggable controllers, meaning

//you must always either restart your Arduino after you conect the controller,

//or call config_gamepad(pins) again after connecting the controller.

int error = 0;

byte type = 0;

byte vibrate = 0;
int ENA=2;
int IN1=3;
int IN2=4;
int IN3=5;
int IN4=6;
int ENB=7;

int ENA1=A0;
int IN11=A1;
int IN12=A2;
int IN13=A3;
int IN14=A4;
int ENB1=A5;


void setup() {
  // put your setup code here, to run once:


 pinMode(ENA,OUTPUT);//output
 pinMode(ENB,OUTPUT);
 pinMode(IN1,OUTPUT);
 pinMode(IN2,OUTPUT);
 pinMode(IN3,OUTPUT);
 pinMode(IN4,OUTPUT);

 pinMode(ENA1,OUTPUT);//output
 pinMode(ENB1,OUTPUT);
 pinMode(IN11,OUTPUT);
 pinMode(IN12,OUTPUT);
 pinMode(IN13,OUTPUT);
 pinMode(IN14,OUTPUT);

Serial.begin(57600);

 //CHANGES for v1.6 HERE!!! **************PAY ATTENTION*************

 error = ps2x.config_gamepad(13,11,10,12, true, true);   //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error

 if(error == 0){
  
   Serial.println("Found Controller, configured successful");
  digitalWrite(9,OUTPUT);
   Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");

  Serial.println("holding L1 or R1 will print out the analog stick values.");

  Serial.println("Go to www.billporter.info for updates and to report bugs.");

 }

  else if(error == 1)

   Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");

  else if(error == 2)

   Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

  else if(error == 3)

   Serial.println("Controller refusing to enter Pressures mode, may not support it. ");

   //Serial.print(ps2x.Analog(1), HEX);

   type = ps2x.readType();

     switch(type) {

       case 0:

        Serial.println("Unknown Controller type");

       break;

       case 1:

        Serial.println("DualShock Controller Found");

       break;

       case 2:

         Serial.println("GuitarHero Controller Found");

       break;

     }

}



void loop() {
  // put your main code here, to run repeatedly:
           digitalWrite(ENA,HIGH);
           digitalWrite(ENB,HIGH);// High is start driving car
  //forward
           digitalWrite(IN1,LOW); 
           digitalWrite(IN2,LOW);//setting motorA's directon
           digitalWrite(IN3,LOW);
           digitalWrite(IN4,LOW);//setting motorB's directon]


          // digitalWrite(ENA1,HIGH);
          // digitalWrite(ENB1,HIGH);// High is start driving car
  //forward
          // digitalWrite(IN11,LOW); 
          // digitalWrite(IN12,LOW);//setting motorA's directon
          // digitalWrite(IN13,LOW);
          // digitalWrite(IN14,LOW);//setting motorB's directon]


           if(error == 1) //skip loop if no controller found

  return;

 if(type == 2){ //Guitar Hero Controller

   ps2x.read_gamepad();          //read controller

   if(ps2x.ButtonPressed(GREEN_FRET))

     Serial.println("Green Fret Pressed");
     digitalWrite(7,OUTPUT);

   if(ps2x.ButtonPressed(RED_FRET))

     Serial.println("Red Fret Pressed");

   if(ps2x.ButtonPressed(YELLOW_FRET))

     Serial.println("Yellow Fret Pressed");

   if(ps2x.ButtonPressed(BLUE_FRET))

     Serial.println("Blue Fret Pressed");

   if(ps2x.ButtonPressed(ORANGE_FRET))

     Serial.println("Orange Fret Pressed");

    if(ps2x.ButtonPressed(STAR_POWER))

     Serial.println("Star Power Command");

    if(ps2x.Button(UP_STRUM))          //will be TRUE as long as button is pressed

     Serial.println("Up Strum");

    if(ps2x.Button(DOWN_STRUM))

     Serial.println("DOWN Strum");

    if(ps2x.Button(PSB_START))                   //will be TRUE as long as button is pressed

         Serial.println("Start is being held");

    if(ps2x.Button(PSB_SELECT))

         Serial.println("Select is being held");

    if(ps2x.Button(ORANGE_FRET)) // print stick value IF TRUE

    {

        Serial.print("Wammy Bar Position:");

        Serial.println(ps2x.Analog(WHAMMY_BAR), DEC);

    }

 }

 else { //DualShock Controller

    ps2x.read_gamepad(false, vibrate);          //read controller and set large motor to spin at 'vibrate' speed

    if(ps2x.Button(PSB_START))                   //will be TRUE as long as button is pressed

         Serial.println("Start is being held");

    if(ps2x.Button(PSB_SELECT))

         Serial.println("Select is being held");

   

     if(ps2x.Button(PSB_PAD_UP)) {         //will be TRUE as long as button is pressed

       Serial.print("Up held this hard: ");

      Serial.println(ps2x.Analog(PSAB_PAD_UP), DEC);

           digitalWrite(ENA,HIGH);
           digitalWrite(ENB,HIGH);// High is start driving car
  //forward
           digitalWrite(IN1,HIGH); 
           digitalWrite(IN2,LOW);//setting motorA's directon
           digitalWrite(IN3,HIGH);
           digitalWrite(IN4,LOW);//setting motorB's directon]

      }

      if(ps2x.Button(PSB_PAD_RIGHT)){

           


       Serial.print("Right held this hard: ");

        Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);

        digitalWrite(ENA,HIGH);
           digitalWrite(ENB,HIGH);// High is start driving car
  //forward
           digitalWrite(IN1,LOW); 
           digitalWrite(IN2,LOW);//setting motorA's directon
           digitalWrite(IN3,HIGH);
           digitalWrite(IN4,LOW);//setting motorB's directon]


          
      }

      if(ps2x.Button(PSB_PAD_LEFT)){

       Serial.print("LEFT held this hard: ");

        Serial.println(ps2x.Analog(PSAB_PAD_LEFT), DEC);

           digitalWrite(ENA,HIGH);
           digitalWrite(ENB,HIGH);// High is start driving car
  //forward
           digitalWrite(IN1,HIGH); 
           digitalWrite(IN2,LOW);//setting motorA's directon
           digitalWrite(IN3,LOW);
           digitalWrite(IN4,LOW);//setting motorB's directon]

      }

      if(ps2x.Button(PSB_PAD_DOWN)){

       Serial.print("DOWN held this hard: ");

     Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);

      digitalWrite(ENA,HIGH);
           digitalWrite(ENB,HIGH);// High is start driving car
  //forward
           digitalWrite(IN1,LOW); 
           digitalWrite(IN2,HIGH);//setting motorA's directon
           digitalWrite(IN3,LOW);
           digitalWrite(IN4,HIGH);//setting motorB's directon]


      } 

      vibrate = ps2x.Analog(PSAB_BLUE);        //this will set the large motor vibrate speed based on

                                              //how hard you press the blue (X) button   

  

    if (ps2x.NewButtonState())               //will be TRUE if any button changes state (on to off, or off to on)

    {

       

        if(ps2x.Button(PSB_L3))

         Serial.println("L3 pressed");

        if(ps2x.Button(PSB_R3))

         Serial.println("R3 pressed");

        if(ps2x.Button(PSB_L2))

         Serial.println("L2 pressed");

        if(ps2x.Button(PSB_R2))

         Serial.println("R2 pressed");

        if(ps2x.Button(PSB_GREEN)){

         Serial.println("Triangle pressed");

         digitalWrite(ENA1,HIGH);
           digitalWrite(ENB1,HIGH);// High is start driving car
  
           digitalWrite(IN11,LOW); 
           digitalWrite(IN12,LOW);//setting motorA's directon
           digitalWrite(IN13,LOW);
           digitalWrite(IN14,LOW);//setting motorB's directon]
        }

    } 



    if(ps2x.ButtonPressed(PSB_RED))        {     //will be TRUE if button was JUST pressed

         Serial.println("Circle just pressed");

           digitalWrite(ENA1,HIGH);
           digitalWrite(ENB1,HIGH);// High is start driving car
  
           digitalWrite(IN11,LOW); 
           digitalWrite(IN12,LOW);//setting motorA's directon
           digitalWrite(IN13,LOW);
           digitalWrite(IN14,LOW);//setting motorB's directon]

         
           digitalWrite(ENA1,HIGH);
           digitalWrite(ENB1,HIGH);// High is start driving car
  //forward
           digitalWrite(IN11,LOW); 
           digitalWrite(IN12,LOW);//setting motorA's directon
           digitalWrite(IN13,LOW);
           digitalWrite(IN14,HIGH);//setting motorB's directon]
           
           
          

    }

    if(ps2x.ButtonReleased(PSB_PINK))    {         //will be TRUE if button was JUST released

         Serial.println("Square just released");

           digitalWrite(ENA1,HIGH);
           digitalWrite(ENB1,HIGH);// High is start driving car
  //forward
           digitalWrite(IN11,LOW); 
           digitalWrite(IN12,LOW);//setting motorA's directon
           digitalWrite(IN13,HIGH);
           digitalWrite(IN14,LOW);//setting motorB's directon]

    }
    if(ps2x.NewButtonState(PSB_BLUE))  {          //will be TRUE if button was JUST pressed OR released

         Serial.println("X just changed");   

           digitalWrite(ENA1,HIGH);
           digitalWrite(ENB1,HIGH);// High is start driving car
  //forward
           digitalWrite(IN11,LOW); 
           digitalWrite(IN12,HIGH);//setting motorA's directon
           digitalWrite(IN13,LOW);
           digitalWrite(IN14,LOW);//setting motorB's directon]





    }


    if(ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1)) // print stick values if either is TRUE

    {

        Serial.print("Stick Values:");

        Serial.print(ps2x.Analog(PSS_LY), DEC); //Left stick, Y axis. Other options: LX, RY, RX 

        Serial.print(",");

        Serial.print(ps2x.Analog(PSS_LX), DEC);

        Serial.print(",");

        Serial.print(ps2x.Analog(PSS_RY), DEC);

        Serial.print(",");

        Serial.println(ps2x.Analog(PSS_RX), DEC);

    }

 }

 delay(100);
}
