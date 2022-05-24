/**
 * Autor: TCHAR
 * Fecha: 13042022
 * Descripción: 
 */

//Bibliotecas
#include "DHT.h"
#define DHTPIN 2     // Digital pin connected to the DHT sensor
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

//Constantes

const int BOTON_1 = 14;
const int BOTON_2 = 12;
const int BOTON_3 = 13;
const int LED_1 = 15;
const int LED_2 = 16;




// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 3 (on the right) of the sensor to GROUND (if your sensor has 3 pins)
// Connect pin 4 (on the right) of the sensor to GROUND and leave the pin 3 EMPTY (if your sensor has 4 pins)
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE);


//Variables
int dato1;


void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));

  pinMode(BOTON_1, INPUT_PULLUP); //Configurar el pin donde se conecta el boton1
  pinMode(LED_1, OUTPUT); //Configurar el pin donde se conecta el led como
  digitalWrite(LED_1, LOW); //0, false, LOW, 1, TRUE, HIGH

  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
  dato1=!digitalRead(BOTON_1); //Leer el boton1
  digitalWrite(LED_1, dato1); //Escribir en el led lo que trae dato1
  dato2=!digitalRead(BOTON_2); //Leer el boton1
  digitalWrite(LED_2, dato2); //Escribir en el led lo que trae dato1
  dato3=!digitalRead(BOTON_2); //Leer el boton1
  digitalWrite(LED_2, dato3); //Escribir en el led lo que trae dato1
  
  
}
