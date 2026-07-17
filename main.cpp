/*
  Smart Home Automation - ESP32 + DHT22 + Web Server
  ----------------------------------------------------
  - LED1 (GPIO2)  = Tubelight
  - LED2 (GPIO4)  = Fan
  - DHT22 (GPIO15) = Temperature & Humidity sensor
  - Control via a phone/web browser (any device on the same WiFi)
  - /status gives JSON output too, so you can later connect a real app
*/

#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>

#define DHTPIN 15
#define DHTTYPE DHT22
#define LED1_PIN 2   // Tubelight
#define LED2_PIN 4   // Fan

DHT dht(DHTPIN, DHTTYPE);
WebServer server(80);

// Wokwi's built-in simulated WiFi network (works instantly in simulation,
// no real router needed). On real hardware, replace with your own WiFi.
const char* ssid = "Wokwi-GUEST";
const char* password = "";

bool led1State = false;
bool led2State = false;

String htmlPage() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  String page = "<!DOCTYPE html><html><head><title>Smart Home</title>";
  page += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  page += "<style>body{font-family:Arial;text-align:center;background:#f2f2f2;}";
  page += "button{padding:15px 30px;font-size:18px;margin:10px;border-radius:8px;border:none;color:white;}";
  page += ".on{background:#4CAF50;} .off{background:#f44336;}";
  page += ".card{background:white;margin:20px auto;padding:20px;width:300px;border-radius:10px;";
  page += "box-shadow:0 2px 8px rgba(0,0,0,0.15);}</style></head><body>";
  page += "<h2>Smart Home Dashboard</h2>";

  page += "<div class='card'><h3>Temperature & Humidity</h3>";
  page += "<p>Temp: " + String(temp) + " &deg;C</p>";
  page += "<p>Humidity: " + String(hum) + " %</p></div>";

  page += "<div class='card'><h3>Tubelight (LED1)</h3>";
  page += "<a href='/led1on'><button class='on'>ON</button></a>";
  page += "<a href='/led1off'><button class='off'>OFF</button></a>";
  page += "<p>Status: " + String(led1State ? "ON" : "OFF") + "</p></div>";

  page += "<div class='card'><h3>Fan (LED2)</h3>";
  page += "<a href='/led2on'><button class='on'>ON</button></a>";
  page += "<a href='/led2off'><button class='off'>OFF</button></a>";
  page += "<p>Status: " + String(led2State ? "ON" : "OFF") + "</p></div>";

  page += "</body></html>";
  return page;
}

void handleRoot()    { server.send(200, "text/html", htmlPage()); }

void handleLed1On()  { led1State = true;  digitalWrite(LED1_PIN, HIGH); server.sendHeader("Location", "/"); server.send(303); }
void handleLed1Off() { led1State = false; digitalWrite(LED1_PIN, LOW);  server.sendHeader("Location", "/"); server.send(303); }
void handleLed2On()  { led2State = true;  digitalWrite(LED2_PIN, HIGH); server.sendHeader("Location", "/"); server.send(303); }
void handleLed2Off() { led2State = false; digitalWrite(LED2_PIN, LOW);  server.sendHeader("Location", "/"); server.send(303); }

// JSON API - useful later if you build a real phone app (Flutter/Blynk/etc)
void handleStatus() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  String json = "{";
  json += "\"temperature\":" + String(temp) + ",";
  json += "\"humidity\":" + String(hum) + ",";
  json += "\"led1\":" + String(led1State ? "true" : "false") + ",";
  json += "\"led2\":" + String(led2State ? "true" : "false");
  json += "}";
  server.send(200, "application/json", json);
}

void setup() {
  Serial.begin(115200);
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  dht.begin();

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected! Open this in a browser: http://");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/led1on", handleLed1On);
  server.on("/led1off", handleLed1Off);
  server.on("/led2on", handleLed2On);
  server.on("/led2off", handleLed2Off);
  server.on("/status", handleStatus);
  server.begin();
}

void loop() {
  server.handleClient();
}
