da /******************************************
 *
 * This example works for both Industrial and STEM users.
 *
 * Developed by Jose Garcia, https://github.com/jotathebest/
 *
 * ****************************************/

/****************************************
 * Include Libraries
 ****************************************/
#include "UbidotsEsp32Mqtt.h"
#include "DHT.h"
#define DHTTYPE DHT11

/****************************************
 * Define Constants
 ****************************************/
const char *UBIDOTS_TOKEN = "BBFF-Sreeo9EYDM7l1cyzoD4hwg54yqMmhi";  // Put here your Ubidots TOKEN
const char *WIFI_SSID = "UTNG_Docencia";      // Put here your Wi-Fi SSID
const char *WIFI_PASS = "UtNg2020@#$";      // Put here your Wi-Fi password
const char *DEVICE_LABEL = "demo_device";   // Put here your Device label to which data  will be published
const char *VARIABLE_LABEL = "demo_var"; // Put here your Variable label to which data  will be published



const int PUBLISH_FREQUENCY = 5000; // Update rate in milliseconds

unsigned long timer;
uint8_t analogPin = 27; // Pin used to read data from GPIO34 ADC_CH6.

DHT dht(analogPin, DHTTYPE);
Ubidots ubidots(UBIDOTS_TOKEN);

/****************************************
 * Auxiliar Functions
 ****************************************/

void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

/****************************************
 * Main Functions
 ****************************************/

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  // ubidots.setDebug(true);  // uncomment this to make debug messages available
  ubidots.connectToWifi(WIFI_SSID, WIFI_PASS);
  ubidots.setCallback(callback);
  ubidots.setup();
  ubidots.reconnect();

  timer = millis();
}

void loop()
{
  delay(2000);
  float valueH = dht.readHumidity();
  float valueT = dht.readTemperature();
  if (isnan(valueH) || isnan(valueT)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print(F("Humedad: "));
  Serial.print(valueH);
  Serial.print(F("% Temperatura: "));
  Serial.print(valueT);
  Serial.println(F("°C "));
  // put your main code here, to run repeatedly:
  if (!ubidots.connected())
  {
    ubidots.reconnect();
  }
  if (abs(millis() - timer) > PUBLISH_FREQUENCY) // triggers the routine every 5 seconds
  {
    ubidots.add(VARIABLE_LABEL, valueH); // Insert your variable Labels and the value to be sent
    ubidots.publish(DEVICE_LABEL);
    timer = millis();
  }
  ubidots.loop();
}
