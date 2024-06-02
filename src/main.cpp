#include <Arduino.h>



int ein = 0;
int aus = 1;


void setup ( ) {
  //Initialisiert Pin 14 (LED1) als output und Pin 0 und 1 als Input
  pinMode(14, OUTPUT);
  pinMode(0, INPUT);
  pinMode(1, INPUT);
}

// LED1 blinkt im Zweisekundentakt
void loop(){
  
  
  if(digitalRead(ein)) digitalWrite(14, HIGH); // LED1 an, wenn Taster 1 gedrückt wird
  
  if(digitalRead(aus)) digitalWrite(14, LOW); // LED1 aus, wenn Taster 2 gedrückt wird

}