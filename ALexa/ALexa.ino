#include<WiFi.h>
#include<WebServer.h>
#include<Espalexa.h>

#include<ESP32Servo.h>

const char* ssid = "Vodafone-9EC4";
const char* PASSWORD = "";

WebServer server(80);
Servo myServo;
const int servoPin = 13;

Espalexa espalexa;

void servoOn(){
  myServo.write(180);
  
}

void servoOff(){
  myServo.write(0);
}

void handleOn() {
  servoOn();
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleOff() {
  servoOff();
  server.sendHeader("Location", "/");
  server.send(303);
}


void alexaServoControl(uint8_t brightness) {
  if (brightness == 0) {
    servoOff();
    Serial.println("Alexa → OFF");
  } else {
    servoOn();
    Serial.println("Alexa → ON");
  }
}


void handleRoot() {
  String page = "<html><body>";
  page += "<h1>ESP32 Servo Control</h1>";
  page += "<a href='/on'><button style='width:150px;height:60px'>ON</button></a><br><br>";
  page += "<a href='/off'><button style='width:150px;height:60px'>OFF</button></a>";
  page += "</body></html>";

  server.send(200, "text/html", page);
}

void handleNotFound() {
  String req  = server.uri();
  String body = server.hasArg("plain") ? server.arg("plain") : "";
  if (!espalexa.handleAlexaApiCall(req, body)) {
    server.send(404, "text/plain", "Not found");
  }
}

void setup() {
  Serial.begin(115200);

  myServo.setPeriodHertz(50);
  myServo.attach(servoPin, 500, 2400);
  myServo.write(90);

  WiFi.begin(ssid, PASSWORD);
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println(".");
  }
  Serial.println();
  Serial.println("Connected!");
  Serial.println("IP: ");
  Serial.println(WiFi.localIP());

  espalexa.addDevice("light", alexaServoControl);

  // Web server routes
  server.on("/", handleRoot);
  server.on("/on", handleOn);
  server.on("/off", handleOff);
  server.begin();
  Serial.println("Web server started");
  server.onNotFound(handleNotFound);

  espalexa.begin(&server);
  server.begin();
  Serial.println("Ready!");


}

void loop() {
  espalexa.loop();
  server.handleClient();
 
  

}
