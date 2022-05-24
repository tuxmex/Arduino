
/*
 * Ejemplo DHT 11
 * Por: GoT
 * Fecha: 18 de abril del 2022
 * 
 * Este programa es realizando comparaciones
 */

#include "DHT.h"

// declaracion de variables
#define DHTPIN 5
#define DHTTYPE DHT11

#define BTN_M 2
#define BTN_AD 3
#define BTN_SCF 4

const int LED1 = 6;
const int LED2 = 7;

int dato1;
int dato2;
int dato3;
float dato;
int d=10;

// Configuración de entradas y salidas

DHT dht(DHTPIN, DHTTYPE);
void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(BTN_M,INPUT);
  pinMode(BTN_AD,INPUT);
  pinMode(BTN_SCF,INPUT);
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);

}

// Codigo principal del programa

void loop() {
  dato = dht.readTemperature();
  dato1 = digitalRead (BTN_M);
  dato2 = digitalRead (BTN_AD);
  dato3 = digitalRead (BTN_SCF);
  
  if ((dato > 31)&&(dato1 == 0))
  {
    if ((dato2 == 1)||(dato3 == 1))
    {
      digitalWrite (LED1,HIGH);
      digitalWrite (LED2,HIGH);  
    }
    else
    {
      digitalWrite (LED1,LOW);
      digitalWrite (LED2,HIGH); 
    }
  }
  else if ((dato1 == 1) && (t < 31))
  {
    digitalWrite (LED1,HIGH);
    digitalWrite (LED2,LOW);
  }
  else if ((dato1 == 1)&& (t > 31))
  {
    
    if ((dato2 == 1)||(dato3 == 1))
    {
      digitalWrite (LED1,HIGH);
      digitalWrite (LED2,HIGH);
    }
    else
    {
      digitalWrite (LED1,HIGH);
      digitalWrite (LED2,LOW); 
    }
  }
  else
  {
    if ((dato2 == 1)||(dato3 == 1))
    {
      digitalWrite (LED1,LOW);
      digitalWrite (LED2,HIGH);
    }
    else
    {
      digitalWrite (LED1,LOW);
      digitalWrite (LED2,LOW);
    }
  }
  
  delay (d);
}
