#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <SoftTimer.h>
#include <DelayRun.h>

const char* ssid = "***";
const char* password = "***";

void myLoop(Task* me);
bool turnOff(Task* me);

Task loopTask(0, myLoop);
DelayRun turnOffTask(1000, turnOff);

ESP8266WebServer server(80);

const int led = 2;

void handleRoot() {
  server.send(200, "text/html",
    "<html><body><button type=\"button\" onclick=\"var xhttp = new XMLHttpRequest();xhttp.open('GET', '/click', true);xhttp.send();\">Click Me!</button></body></html>"
  );
}

void setup(void){
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/click", [](){
    digitalWrite(led, LOW);
    Serial.println("Clicked");
    turnOffTask.startDelayed();
    server.send(200, "text/plain", "Okay");
  });

  server.begin();
  Serial.println("HTTP server started");
  SoftTimer.add(&loopTask);
  digitalWrite(led, HIGH);
}

void myLoop(Task* me) {
  ESP.wdtFeed();
  server.handleClient();
}

bool turnOff(Task* me)
{
  digitalWrite(led, HIGH);
}

