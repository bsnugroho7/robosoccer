#define LED1 5
#define LED2 6
int input;
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
      Serial.begin(9600);
      analogWrite(LED1, 0);
      analogWrite(LED2,0);
}

// the loop function runs over and over again forever
void loop() {
  if (Serial.available()){
    input=Serial.read();
  }
    switch(input){
      case '1': analogWrite(LED1, 255);
                analogWrite(LED2, 255); break;
      case '2': analogWrite(LED1, 0 ); 
                analogWrite(LED2, 0); break; 
    }
    /*if(input=='1'){
    analogWrite(LED1, 255);   // turn the LED on (HIGH is the voltage level)
    Serial.println("Terbaca");
    };
                      // wait for a second
    if(input=='0'){
    analogWrite(LED1, 0);    // turn the LED off by making the voltage LOW
    Serial.println("Mati");
    };*/
}
  
