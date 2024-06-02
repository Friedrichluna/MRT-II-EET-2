#include <Arduino.h>

// put function declarations here:
int myFunction(int, int);

void setup ( ) {
  //Initialisiert Pin 14 (LED1) als output .
  pinMode(14, OUTPUT);
}

// LED1 blinkt im Zweisekundentakt
void loop(){
  digitalWrite(14, HIGH); // LED1 an
  delay(1000); // 1000 ms warten
  digitalWrite(14, LOW); // LED1 aus
  delay(1000); // 1000 ms warten
}