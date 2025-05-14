#include "GreenHouse.h"

float GreenHouse::readTemp() {
  byte i;
  byte present = 0;
  byte type_s;
  byte data[12];
  byte addr[8];
 
  if (!tempOneWire_.search(addr)) {
    tempOneWire_.reset_search();
    return NAN;
  }
 
  if (OneWire::crc8(addr, 7) != addr[7]) {
    return NAN;
  }
 
  switch (addr[0]) {
    case 0x10:
      type_s = 1;
      break;
    case 0x28:
    case 0x22:
      type_s = 0;
      break;
    default:
      Serial.println("Неизвестный тип датчика.");
      return NAN;
  }
 
  tempOneWire_.reset();
  tempOneWire_.select(addr);
  
  tempOneWire_.write(0x44);
 
  delay(1000);
 
  present = tempOneWire_.reset();
  tempOneWire_.select(addr);
  tempOneWire_.write(0xBE);
 
  for (i = 0; i < 9; i++) {
    data[i] = tempOneWire_.read();
  }
 
  int16_t raw = (data[1] << 8) | data[0];
  float celsius = 0.0;
 
  if (type_s == 1) {
    raw = raw << 3;
    if (data[7] == 0x10) {
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  } else {
    byte cfg = (data[4] & 0x60);
    if (cfg == 0x00) raw = raw & ~7;
    else if (cfg == 0x20) raw = raw & ~3;
    else if (cfg == 0x40) raw = raw & ~1;
  }
  celsius = (float)raw / 16.0;
 
  return celsius;
}

static const int LDR_WINDOW = 250;

void GreenHouse::manageLight()
{
  int ldrValue = readLight();

  if (ldrValue > (prevLdrValue - LDR_WINDOW) && ldrValue < (prevLdrValue + LDR_WINDOW)) {
    return;
  }

  if (ldrValue > 1800) {
    turnLightOn();
  } else {
    turnLightOff();
  }
  
}
