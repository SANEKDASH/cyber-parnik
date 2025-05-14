#ifndef GREEN_HOUSE_HEADER
#define GREEN_HOUSE_HEADER

#include <OneWire.h>
#include <WiFi.h>
#include <WebServer.h>
#include <DallasTemperature.h>
#include <Arduino.h>

static const int ONE_WIRE_TEMP_BUS = 22;
static const int WATER_FLOW_PIN = 5;
static const int LIGHT_PIN = 4;
static const int LDR_PIN = 34;

class GreenHouse {  
  OneWire tempOneWire_;

  int tempPin_;
  int waterPin_;
  int lightPin_;
  int ldrPin_;

  int prevLdrValue;
public:
  GreenHouse() : tempOneWire_(ONE_WIRE_TEMP_BUS), tempPin_(ONE_WIRE_TEMP_BUS), 
                 waterPin_(WATER_FLOW_PIN), lightPin_(LIGHT_PIN),
                 ldrPin_(LDR_PIN), prevLdrValue(0) {    
	  pinMode(waterPin_, OUTPUT);
    turnPumpOff();
    pinMode(lightPin_, OUTPUT);
    turnLightOff();
    
	  Serial.begin(9600);  	
  }

  void pumpWater() {turnPumpOn(); delay(5); turnPumpOff();}
  void turnPumpOn()  { digitalWrite(waterPin_, HIGH); }
  void turnPumpOff() { digitalWrite(waterPin_, LOW); }
  
  void turnLightOn()  { digitalWrite(lightPin_, HIGH); }
  void turnLightOff() { digitalWrite(lightPin_, LOW); }
  
  int readLight() { return analogRead(ldrPin_); }

  void manageLight();

  float readTemp();

  ~GreenHouse() {}
};
#endif /* GREEN_HOUSE_HEADER */
