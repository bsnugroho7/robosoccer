#define LED_BUILTIN 13
int input;
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
      Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  if (Serial.available()){
    input=Serial.read();
  }
    if(input=='1'){
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    Serial.println("Terbaca");
    }
                      // wait for a second
    if(input=='0'){
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    Serial.println("Mati");
    }
}
  
