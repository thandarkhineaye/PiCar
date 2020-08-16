#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "";      //Wi-Fi Name
const char* password = "";   // Wi-Fi Password

ESP8266WebServer server(80);
//the current condition of car (assigne 's' for STOP condition)
char Carstatus = 's';

uint8_t L298N_IN1_PIN = D1; //GPI04
uint8_t L298N_IN3_PIN = D2; // GPI02

String handleCar(char cs) {
  String message = "<!DOCTYPE html> <html>\n";
  message +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";


  message += "<html> <head> <title>PI CAR</title><head>";
  message += "<body><h3>PI CAR</h1>";
  if(cs == 'f')
  {
  message +="<h3>MOVING FORWARD</h3>\n";
  }
  message += "<table> ";
  message += "<tr>";
  message += "<td><p><a href=\"/forward\"><button style=\"width:100;height:100;font-size:100px;\" class=\"button\">^</button></a></p> ";
  message += "<tr>";
  message += "</table> ";
  message += "</body></html>";
  return message;
}


void setup() {
  //Set Serial Number
  Serial.begin(115200);
  //Assign pin mode as OUTPUT
  pinMode(L298N_IN1_PIN, OUTPUT);
  pinMode(L298N_IN3_PIN, OUTPUT);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected to ");
  Serial.println(ssid);
  Serial.println("IP address:");
  Serial.println(WiFi.localIP());

  //Default Page
  server.on("/", handleRoot);
  //Forward Page
  server.on("/forward", handle_forward);
  //Backward Page
  server.on("/stop", handle_stop);
  //Left Page
  server.on("/left", handle_left);
  //Right Page
  server.on("/right", handle_right);
  
  //Back Page
  server.on("/backward", handle_back);
 
  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");

}

void loop() {
  server.handleClient();

  if(Carstatus == 'f' ){
    carForward();
  }
}
void carForward(){
  //Forward Condition you have to make First two IN1 and IN3 as HIGH
  //Serial.print("I am in carforward");
  digitalWrite(L298N_IN1_PIN, HIGH);
  digitalWrite(L298N_IN3_PIN, HIGH);

  //IN2 and IN4 はまだ関係がないですから、LOW にしてください。
  //digitalWrite( LEFTmotor1, LOW);
  //digitalWrite( RIGHTmotor1, LOW);
}
void handleNotFound() {
  String message = "File Not Found ¥n¥n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}
void handleRoot() {
  server.send(200, "text/plain", "hello from esp8266!");
}
void handle_stop(){
  Carstatus = 's';
  Serial.println("STOP");
  server.send(200, "text/html", handleCar(Carstatus));
}
void handle_forward(){
  Carstatus = 'f';
  Serial.println("FORWARD");
  //Serial.println(Carstatus);
  server.send(200, "text/html", handleCar(Carstatus));
}
void handle_left(){
  Carstatus = 'l';
  Serial.println("TURN LEFT");
  server.send(200, "text/html", handleCar(Carstatus));
}
void handle_right(){
  Carstatus = 'r';
  Serial.println("RIGHT");
  server.send(200, "text/html", handleCar(Carstatus));
}
void handle_back(){
  Carstatus = 'b';
  Serial.println("Back");
  server.send(200, "text/html", handleCar(Carstatus));
}
