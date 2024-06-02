#include <Arduino.h>

#define T_ON 10 //Zeit in der der Triac-Pin an ist
#define MIN_ZUENDWINKEL 6
#define MAX_ZUENDWINKEL 176

int ein = 0; //Taster 0
int aus = 1; //Taster 1
int triac = 3; //Gibt Gatestrom an Triac
int eingangspin = 6; //bei Nulldurchgang von Netz auf High
int interrupt_pin = 9;
int debug1 = 14; //Debug LED1
int debug2 = 15; //Debug LED2

int null_zaehler = 0;
bool lampe_an = false;
int zuendwinkel = 30; //Zuendwinkel in Grad
int verzoegerung_triac = (zuendwinkel* 10000)/180 ;  //Verzögerung in Mikrosekunden


void rising_edge_interrupt(){
  null_zaehler++;
  //Wechsel Lampe Ein/Aus aller 50 Nulldurchgänge
  if(null_zaehler % 50){
    lampe_an = !lampe_an;
  } 
  verzoegerung_triac = (zuendwinkel * 10000)/180; //aktualisiert Verzögerung
  delayMicroseconds(verzoegerung_triac);
  if(lampe_an){
    digitalWrite(triac, HIGH);
    delayMicroseconds(T_ON);
    digitalWrite(triac, LOW);
  }


  //Zündwinkel mit Taster verändern
  if(digitalRead(ein)) {
    digitalWrite(debug1, HIGH); // LED1 an, wenn Taster 1 gedrückt wird
    if (zuendwinkel > MIN_ZUENDWINKEL ) {
      zuendwinkel--;
    }
  }
  else {
    digitalWrite(debug1, LOW);
  }

  if(digitalRead(aus)) {
    digitalWrite(debug1, HIGH); // LED1 an, wenn Taster 2 gedrückt wird
    if (zuendwinkel < MAX_ZUENDWINKEL) {
      zuendwinkel++;
    }
  }
  else {
    digitalWrite(debug1, LOW);
  }
}



void setup ( ) {
  //Initialisiert Pins
  pinMode(debug1, OUTPUT);
  pinMode(triac, OUTPUT);
  pinMode(ein, INPUT);
  pinMode(aus, INPUT);

  attachInterrupt(digitalPinToInterrupt(interrupt_pin), rising_edge_interrupt, RISING);

}

// LED1 wird durch einen Taster eingeschaltet und durch anderen Taster wieder aus
void loop(){
  //debug LED2
  if(lampe_an) {
    digitalWrite(debug2, HIGH); // LED2 am, wenn Lampe an ist
  }
  else {
    digitalWrite(debug2, LOW);
  }
}