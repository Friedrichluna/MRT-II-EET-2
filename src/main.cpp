#include <Arduino.h>

#define T_MIN_I_HOLD 300 //Zeit nach Nulldurchgang bis Haltestrom fließt in ms
#define T_ON 10 //Zeit in der der Triac-Pin an ist

int ein = 0; //Taster 0
int aus = 1; //Taster 1
int triac = 3; //Gibt Gatestrom an Triac
int eingangspin = 6; //bei Nulldurchgang von Netz auf High
int debug1 = 14; //Debug LED1
int debug2 = 15; //Debug LED2

int null_zaehler = 0;
bool lampe_an = false;
int zuendwinkel = 30; //Zuendwinkel in Grad
int verzoegerung_triac = zuendwinkel/180 * 10000;  //Verzögerung in Mikrosekunden

void setup ( ) {
  //Initialisiert Pins
  pinMode(debug1, OUTPUT);
  pinMode(triac, OUTPUT);
  pinMode(ein, INPUT);
  pinMode(aus, INPUT);

  // Setz den Zündwinkel auf den minimal zugelassenen
  if(verzoegerung_triac < T_MIN_I_HOLD){
    verzoegerung_triac = T_MIN_I_HOLD;
    Serial.println("Verzögerung zu klein");
  }
}

bool rising_edge(int value) {
  static int old_value;
  bool edge = false;
  if ((value == 1) && (old_value == 0) ){
    edge = true;
  }
  old_value = value;
  return edge;
}



// LED1 wird durch einen Taster eingeschaltet und durch anderen Taster wieder aus
void loop(){
  if (rising_edge(digitalRead(eingangspin))){ //wird im Nulldurchgang aktiviert:
    null_zaehler++;
    //Wechsel Lampe Ein/Aus aller 50 Nulldurchgänge
    if(null_zaehler % 50){
      lampe_an = !lampe_an;
    } 
    delayMicroseconds(verzoegerung_triac);
    if(lampe_an){
      digitalWrite(triac, HIGH);
      delayMicroseconds(T_ON);
      digitalWrite(triac, LOW);
    }
  }
  
  //debug LED
  if(digitalRead(ein)) {
    digitalWrite(debug1, HIGH); // LED1 an, wenn Taster 1 gedrückt wird
  }
  else {
    digitalWrite(debug1, LOW);
  }
  if(lampe_an) {
    digitalWrite(debug2, HIGH); // LED2 am, wenn Lampe an ist
  }
  else {
    digitalWrite(debug2, LOW);
  }

}