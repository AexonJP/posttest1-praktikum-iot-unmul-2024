/*
  Rui Santos
  Complete project details at Complete project details at https://RandomNerdTutorials.com/esp8266-nodemcu-http-get-post-arduino/

  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
  
  Code compatible with ESP8266 Boards Version 3.0.0 or above 
  (see in Tools > Boards > Boards Manager > ESP8266)
*/
// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

// #include "DHT.h"


// // #define DHTPIN D2    // Digital pin connected to the DHT sensor
// // Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// // Pin 15 can work but DHT must be disconnected during program upload.

// // Uncomment whatever type you're using!
// #define DHTTYPE DHT11   // DHT 11
// #define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

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
// DHT dht(DHTPIN, DHTTYPE);


#include <DHT.h>

#include <ESP8266WiFi.h>
#include <String.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <bits/stdc++.h> 

#define DHTPIN D5 // pin digital sensor DHT11
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "Universitas Mulawarman";
const char* password = "";

//Your Domain name with URL path or IP address with path
const char* serverName = "http://10.10.201.143:5000/api/add_message/aeoxnid";

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 200;

void setup() {
  Serial.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D7, INPUT_PULLUP);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
  dht.begin();
}

void loop() {
  //Send an HTTP POST request every 10 minutes
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;
      
      // Your Domain name with URL path or IP address with path
      http.begin(client, serverName);
      // http.
  
      // If you need Node-RED/server authentication, insert user and password below
      //http.setAuthorization("REPLACE_WITH_SERVER_USERNAME", "REPLACE_WITH_SERVER_PASSWORD");

      // Specify content-type header
      http.addHeader("Content-Type", "application/json");

      float h = dht.readHumidity();
      // Read temperature as Celsius (the default)
      float t = dht.readTemperature();
      // Read temperature as Fahrenheit (isFahrenheit = true)
      // float f = dht.readTemperature(true);

      

      // // Check if any reads failed and exit early (to try again).
      // if (isnan(h) || isnan(t) || isnan(f)) {
      //   Serial.println(F("Failed to read from DHT sensor!"));
      //   return;
      // }

      // // Compute heat index in Fahrenheit (the default)
      // float hif = dht.computeHeatIndex(f, h);
      // // Compute heat index in Celsius (isFahreheit = false)
      // float hic = dht.computeHeatIndex(t, h, false);
      // char *hcc = dtostrf(hic, 6, 2, hc);
      
      // char hs = dtostrf(hss, 6, 2, hs);;
      // char ts = dtostrf(tss, 6, 2, ts);
      // char hc = hcc;

      int httpResponseCode = http.POST("{\"pesan\":\"terhubung bos dengan esp8266\"}");
      String balasan = http.getString();
      // char *iko = balasan.c_str();
      Serial.println(balasan.c_str());
      if(balasan.substring(0, 1) == "1"){
        digitalWrite(D2, HIGH);
      }
      else if(balasan.substring(0, 1) == "2"){
        digitalWrite(D2, LOW);
      }

      if(balasan.substring(1, 2) == "1"){
        digitalWrite(D3, HIGH);
        // tone(D3, 100);
      }
      else if(balasan.substring(1, 2) == "2"){
        digitalWrite(D3, LOW);
        // noTone(D3);      

      }

      // if(!digitalRead(D7)){
      //   tone(D3, 100);
      // }
      // else{
      //   noTone(D7);
      // }

      // Serial.print("Humidity: ");
      // Serial.print(h);
      // Serial.print("Temperature: ");
      // Serial.print(t);
      // // Send HTTP POST request
      // // int httpResponseCode = http.POST(httpRequestData);
      
      // // If you need an HTTP request with a content type: application/json, use the following:
      // //http.addHeader("Content-Type", "application/json");
      
      // // String ik = ;
      // // String lo = ;
      // // String kk = ;
      int httpResponseCodes = http.POST("{\"Humidity:\":\""+String(h, 5)+"\",\"Temperature C:\":\""+String(t, 5)+"\"}");

      // If you need an HTTP request with a content type: text/plain
      //http.addHeader("Content-Type", "text/plain");
      //int httpResponseCode = http.POST("Hello, World!");
     
      // Serial.print("HTTP Response code: ");
      // Serial.println(httpResponseCode);
      // if(httpResponseCode == 200){
      //   Serial.println("terhubung dengan server");
      // }
        
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}