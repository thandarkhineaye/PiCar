#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "W04_44C3465CEA14";      //Wi-Fi Name
const char* password = "q19q6yhe2yna8b3";   // Wi-Fi Password

ESP8266WebServer server(80);

const byte L298N_A_pin = D1; // GPI05
const byte L298N_A_In1_pin = D2; //GPI04
const byte L298N_A_In2_pin = D3; //GPI0

const byte L298N_B_In4_pin = D4; // GPI02
const byte L298N_B_In3_pin = D5; // GPIO14
const byte L298N_B_pin = D6; //GPI12

int emaSpeed = 900;
int embSpeed = 900;
/*
const byte Led1_pin =  D7; //GPIO13  // Sol Sinyal
const byte Led2_pin =  D8; //GPIO15  // Sag Sinyal 
const byte Led3_pin =  D9; //GPIO3   // On Far 
const byte Led4_pin = D10; //GPI01   // Arka Lamba
const byte Korna_pin = D0; //GPI016  //Korna
byte SolSinyal = 0;
byte SagSinyal = 0;
byte ArkaLamba = 0;
*/



void motorSpeed(int prmA, byte prmA1, byte prmA2, int prmB, byte prmB1, byte prmB2)
{
  analogWrite(L298N_A_pin,prmA);
  analogWrite(L298N_B_pin,prmB);
  
  digitalWrite(L298N_A_In1_pin,prmA1);
  digitalWrite(L298N_A_In2_pin,prmA2);
  digitalWrite(L298N_B_In4_pin,prmB1);
  digitalWrite(L298N_B_In3_pin,prmB2);

}

void handleRoot() {
  server.send(200, "text/plain", "hello from esp8266!");
 }

void handleCar() {
 String message = "";
 int BtnValue = 0;
  for (uint8_t i = 0; i < server.args(); i++) {
    if (server.argName(i)=="a")
    {
      String s = server.arg(i);
      BtnValue = s.toInt();
    }
    Serial.println(server.argName(i) + ": " + server.arg(i) + "\n");
  }
  
  switch (BtnValue) {
   case 11: // 460
      emaSpeed = 460;
      embSpeed = 460;
      break;
   case 22: // 564
      emaSpeed = 564;
      embSpeed = 564;
     break;
   case 33:// 900  
      emaSpeed = 900;
      embSpeed = 900;
     break;
  case 44:// 1023   
      emaSpeed = 1023;
      embSpeed = 1023;
     break;
  }  

  switch (BtnValue) {
   case 1: // sola donuş
     motorSpeed(emaSpeed,LOW,LOW,embSpeed,HIGH,LOW); 
      /*SolSinyal = 1;
      digitalWrite(Led1_pin,HIGH);*/
      break;
   case 2: // düz ileri
     motorSpeed(emaSpeed,HIGH,LOW,embSpeed,HIGH,LOW); 
     /*SolSinyal = 0;
     SagSinyal = 0;
     //digitalWrite(Led1_pin,LOW);
     //digitalWrite(Led2_pin,LOW);*/
     break;
  case  3:// saga donuş  
     motorSpeed(emaSpeed,HIGH,LOW,embSpeed,LOW,LOW); 
     /*SagSinyal = 1;
     //digitalWrite(Led2_pin,HIGH);*/
     break;
  case  4:// tam sola donuş   
     motorSpeed(emaSpeed,LOW,HIGH,embSpeed,HIGH,LOW); 
     /*SolSinyal = 1;
     digitalWrite(Led1_pin,HIGH);*/
     break;
  case 5: // stop   
     motorSpeed(emaSpeed,LOW,LOW,embSpeed,LOW,LOW); 
     /*SolSinyal = 0;
     SagSinyal = 0;
     digitalWrite(Led1_pin,LOW);
     digitalWrite(Led2_pin,LOW);*/
     break;     
  case  6://   
     motorSpeed(emaSpeed,HIGH,LOW,embSpeed,LOW,HIGH); 
     /*SagSinyal = 1;
    digitalWrite(Led2_pin,HIGH);*/
    break;
  case 7://sol geri
    motorSpeed(emaSpeed,LOW,LOW,embSpeed,LOW,HIGH); 
    break;
  case 8:// tam geri
    motorSpeed(emaSpeed,LOW,HIGH,embSpeed,LOW,HIGH);      
    break;    
  case 9:// sag geri  
    motorSpeed(emaSpeed,LOW,HIGH,embSpeed,LOW,LOW); 
    default:
    break;
  }
 /*
  if (BtnValue > 7)
  {
    ArkaLamba = 1;
    SolSinyal = 1;
    SagSinyal = 1;
    digitalWrite(Led1_pin,HIGH);
    digitalWrite(Led2_pin,HIGH);
    digitalWrite(Led4_pin,HIGH);
  }
  else
  {
    ArkaLamba = 0;
    digitalWrite(Led4_pin,LOW);
  }
 */
  message += "<html> <head> <title>Gungor yalcin</title><head>";
  message += "<body><h3>Wifi Robot Car NodeMCU  Web Server</h1>";
  
  message += "<table> "; 
  message += "<tr>";
  message += "<td><p><a href=\"/car?a=11\"><button style=\"width:100;height:100;font-size:100px;\" class=\"button\">1</button></a></p> ";
  message += "<td><p><a href=\"/car?a=22\"><button style=\"width:100;height:100;font-size:100px;\" class=\"button\">2</button></a></p> ";
  message += "<td><p><a href=\"/car?a=33\"><button style=\"width:100;height:100;font-size:100px;\" class=\"button\">3</button></a></p> ";
  message += "<td><p><a href=\"/car?a=44\"><button style=\"width:100;height:100;font-size:100px;\" class=\"button\">4</button></a></p> ";
  message += "<tr>";
  message += "</table> "; 
  
  message += "<table> "; 
  message += "<tr>";
  message += "<td><p><a href=\"/car?a=1\"><button style=\"width:100;height:100;font-size:100px;\" class=\"button\">\\</button></a></p> ";
  message += "<td><p><a href=\"/car?a=2\"><button style=\"width:100;height:100;font-size:100px;\" class=\"button\">^</button></a></p> ";
  message += "<td><p><a href=\"/car?a=3\"><button style=\"width:100;height:100;font-size:100px;\" class=\"button\">/</button></a></p> ";
  message += "<tr>";
  message += "<td><p><a href=\"/car?a=4\"><button style=\"width:100;height:100;font-size:100px;\" class=\"button\"> < </button></a></p> ";
  message += "<td><p><a href=\"/car?a=5\"><button style=\"width:100;height:100;font-size:100px;\" class=\"button\"> o </button></a></p> ";
  message += "<td><p><a href=\"/car?a=6\"><button style=\"width:100;height:100;font-size:100px;\" class=\"button\"> > </button></a></p> ";
  message += "<tr>";
  message += "<td><p><a href=\"/car?a=7\"><button style=\"width:100;height:100;font-size:100px;\" class=\"button\">/</button></a></p> ";
  message += "<td><p><a href=\"/car?a=8\"><button style=\"width:100;height:100;font-size:100px;\" class=\"button\">v</button></a></p> ";
  message += "<td><p><a href=\"/car?a=9\"><button style=\"width:100;height:100;font-size:100px;\" class=\"button\">\\</button></a></p> ";
  message += "</table> "; 
  message += "</body></html>";
  server.send(200, "text/html", message);
 }

/*
void tempSinyal()
{
  if (SolSinyal==1)
    digitalWrite(Led1_pin,!digitalRead(Led1_pin));

  if (SagSinyal==1)
    digitalWrite(Led2_pin,!digitalRead(Led2_pin));

  if (ArkaLamba==1)
    digitalWrite(Led4_pin,!digitalRead(Led4_pin));

}
*/

void handleNotFound() {
  String message = "File Not Found\n\n";
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
 

void setup() {
 
  pinMode(L298N_A_In1_pin,OUTPUT);
  pinMode(L298N_A_In2_pin,OUTPUT);
  pinMode(L298N_B_In4_pin,OUTPUT);
  pinMode(L298N_B_In3_pin,OUTPUT);

  digitalWrite(L298N_A_In1_pin,LOW);
  digitalWrite(L298N_A_In2_pin,LOW);
  digitalWrite(L298N_B_In4_pin,LOW);
  digitalWrite(L298N_B_In3_pin,LOW);
/*
  pinMode(Led1_pin,OUTPUT);
  pinMode(Led2_pin,OUTPUT);
  pinMode(Led3_pin,OUTPUT);
  pinMode(Led4_pin,OUTPUT);

  digitalWrite(Led1_pin,LOW);
  digitalWrite(Led2_pin,LOW);
  digitalWrite(Led3_pin,LOW);
  digitalWrite(Led4_pin,LOW);
*/ 
 Serial.begin(115200); 
 
   WiFi.mode(WIFI_STA);
   WiFi.begin(ssid, password);
   Serial.println("");
   while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/car", handleCar);

  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
