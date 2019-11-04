#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);
#define MAX_SPEED 1023

//pins defintion, may need changing
const int pin_right   = D1;
const int pin_left    = D2;
const int pin_back    = D3;
const int pin_forward = D4;

void setup(){
    //Set pins as outputs
    pinMode(pin_right, OUTPUT);
    pinMode(pin_left, OUTPUT);
    pinMode(pin_forward, OUTPUT);
    pinMode(pin_back, OUTPUT);
 
    //initialze the Serial Communication
    Serial.begin(115200);
    Serial.println();
    Serial.println("Hello");

    //initialze the Access Point
    WiFi.softAP("iotaCar-AP");
    Serial.println("AP initialized. You may connect to WiFi SSID iotaCar-AP");


    //initialze the mDNS interface
    if (!MDNS.begin("iotacar"))
        Serial.println("Error setting up mDNS responder!");
    else 
        Serial.println("mDNS responder started at http://iotacar.local");

    //register the server handlers
    server.on("/", [](){
        server.send(200, "text/plain", "Hello from the iota Car.");
    });

    server.on("/go-forward", [](){ 
        analogWrite(pin_forward, MAX_SPEED);
        analogWrite(pin_left, 0);
        analogWrite(pin_right, 0);
        analogWrite(pin_back, 0);
        server.send(200, "text/plain", "Car Moving forward."); 
    }); 

    server.on("/go-back", [](){ 
        analogWrite(pin_forward, 0);
        analogWrite(pin_left, 0);
        analogWrite(pin_right, 0);
        analogWrite(pin_back, MAX_SPEED);
        server.send(200, "text/plain", "Car Moving Backward."); 
    }); 

    server.on("/go-left", [](){ 
        analogWrite(pin_forward, MAX_SPEED);
        analogWrite(pin_left, MAX_SPEED);
        analogWrite(pin_right, 0);
        analogWrite(pin_back, 0);
        server.send(200, "text/plain", "Car Moving Left."); 
    }); 

    server.on("/go-right", [](){ 
        analogWrite(pin_forward, MAX_SPEED);
        analogWrite(pin_left, 0);
        analogWrite(pin_right, MAX_SPEED);
        analogWrite(pin_back, 0);
        server.send(200, "text/plain", "Car Moving Right."); 
    }); 

    server.on("/stop", [](){ 
        analogWrite(pin_forward, 0);
        analogWrite(pin_left, 0);
        analogWrite(pin_right, 0);
        analogWrite(pin_back, 0);
        server.send(200, "text/plain", "Car Stopped."); 
    }); 

    //initialize the web-server
    server.begin();
    Serial.println("HTTP server started");
}


void loop(void){
    server.handleClient();
}
