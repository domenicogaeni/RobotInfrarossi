/***************************************************************************
****************************************************************************
    
    BGSCIENZA 2017
    ULTIMA DATA DI MODIFICA: 08/03/2017 DA Domenico Gaeni
    ROBOT INFRAROSSI:
      FUNZIONAMENTO:
        Robot che gira autonomamente all'interno di una stanza ed evita
        gli ostacoli ad una distanza pari a 52 cm.
      
*************************************************************************
*************************************************************************/
#include <Servo.h>

Servo moto_destra;
Servo moto_sinistra;
int sensorpin=A0;  //Pin utilizzato per collegare il ir led SHARP
double distance;
int val, valore;

void setup()
{
   //Attribuisce a valore un seme per trovare un valore casuale
   randomSeed(valore);
   valore=random(0, 2);   
   pinMode(sensorpin, INPUT);
   moto_destra.attach(8);   
   moto_sinistra.attach(7);
   Serial.begin(9600);
}
void loop()
{
   // Leggo il valore dal led infrarossi
   val=analogRead(sensorpin);
   // Converto il segnale ricevuto dal sensore in distanza (cm);
   // con la formula: DISTANZA=9462/(segnale_letto - 16.92)
   distance=9462/(val-16.92);
   // Il led infrarosssi che utilizziamo rileva la distanza a partire da 20 cm;
   // Se il robot rileva un ostacolo a 25 cm di distanza, va a destra o sinistra
   // in base al valore casuale che rileva ogni volta che va avanti;
   // VALORE CASUALE 0: gira a destra;
   // VALORE CASUALE 1: gira a sinistra;
   /*****************************************************************************
   ** N.B. QUALORA IL SENSORE RILEVA UNA DISTANZA MINORE DI 20, LA DISTANZA    **
   ** RESTITUITA DALLA FORMULA SOVRASTANTE E' UN NUMERO MINORE DI 52           **
   ******************************************************************************/
   if(distance<=52)
      if(valore==0) 
        destra();
      else
        sinistra(); 
   else
   {
   // Se il robot non rileva ostacoli va avanti e cambia il valore casuale in modo
   // da farlo svoltare ogni tanto a destra e ogni tanto a sinistra quando la distanza
   // è minore di 25 cm   
      avanti();
      valore=random(0, 2);
   }
   Serial.println(distance);
}
// GIRA A DESTRA
void destra()
{
  moto_destra.write(180);
  moto_sinistra.write(180);
}
//  VA AVANTI
void avanti()
{
  moto_destra.write(0);
  moto_sinistra.write(180);  
}
// GIRA A SINISTRA
void sinistra()
{
  moto_destra.write(0);
  moto_sinistra.write(0);
}
