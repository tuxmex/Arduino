#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
const char ssid[]          = "UTNG_Docencia";
const char pass[]          = "UtNg2020@#$";
const int  port            = 2390;
const String REQUEST_LED_R = "/led_r";
const String REQUEST_LED_G = "/led_g";
const String REQUEST_LED_B = "/led_b";
const char PARAM_VALUE[]   = "value";
const char STATE[]         = "state";
const int  R_PIN           = 12;
const int  G_PIN           = 13;
const int  B_PIN           = 15;
const int MIN_ANALOG = 1023;
const int MAX_ANALOG = 0;
const int MIN_COLOR  = 0;
const int MAX_COLOR  = 255;
AsyncWebServer server(port);
void setup() {
  Serial.begin(115200);
  pinMode(R_PIN, OUTPUT);
  pinMode(G_PIN, OUTPUT);
  pinMode(B_PIN, OUTPUT);
  analogWrite(R_PIN,MIN_ANALOG);
  analogWrite(G_PIN,MIN_ANALOG);
  analogWrite(B_PIN,MIN_ANALOG);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  Serial.print("Connecting ");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println("");
  Serial.print("WiFi connected to: ");
  Serial.println(WiFi.SSID());
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  // Red LED
  server.on(REQUEST_LED_R.c_str(), HTTP_GET, [] (AsyncWebServerRequest *request) {
    // Set LED value
    setLEDvalue(request,R_PIN);
    
    // Send Json response to client
    sendJsonResponse(request);
    
  });
  // Green LED
  server.on(REQUEST_LED_G.c_str(), HTTP_GET, [] (AsyncWebServerRequest *request) {
    // Set LED value
    setLEDvalue(request,G_PIN);
    
    // Send Json response to client
    sendJsonResponse(request);
    
  });
  // Blue LED
  server.on(REQUEST_LED_B.c_str(), HTTP_GET, [] (AsyncWebServerRequest *request) {
    // Set LED value
    setLEDvalue(request,B_PIN);
    
    // Send Json response to client
    sendJsonResponse(request);
    
  });      
  server.onNotFound(notFound);
  server.begin();
}
void setLEDvalue(AsyncWebServerRequest *request, const int pin)
{
  if (request->hasParam(PARAM_VALUE)) 
  {
    int value = request->getParam(PARAM_VALUE)->value().toInt();
    int analogValue = 
           map(value,MIN_COLOR,MAX_COLOR,MIN_ANALOG,MAX_ANALOG);
    analogWrite(pin,analogValue);  
  }
}
void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}
void sendJsonResponse(AsyncWebServerRequest *request) {
  // Create and fill json object for client response
  DynamicJsonBuffer jsonBuffer;
  JsonObject &json = jsonBuffer.createObject();
 
  json[STATE] = "Done!";
  
  AsyncResponseStream *response = 
     request->beginResponseStream("application/json");
  json.printTo(*response);
  request->send(response);          
}
void loop(){}
