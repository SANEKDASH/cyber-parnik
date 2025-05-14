#include "GreenHouse.h"
#include <OneWire.h>

GreenHouse gh;

int timer = 0;

void setup()
{
	Serial.begin(9600);
}

void loop()
{
	gh.manageLight();
	delay(1000 * 10);

	timer += 10;
	if (timer >= 60 * 3) {
		gh.pumpWater();
	}
}