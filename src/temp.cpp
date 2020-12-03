#include <SPI.h>
#include <Adafruit_MAX31855.h>

// Example creating a thermocouple instance with software SPI on any three
// digital IO pins.
#define MAXDO   4
#define MAXCS   5
#define MAXCLK  16

// initialize the Thermocouple
Adafruit_MAX31855 thermocouple(MAXCLK, MAXCS, MAXDO);

void setupThermometer() {
  Serial.begin(9600);
    if (!thermocouple.begin()) {
    Serial.println("ERROR.");
    while (1) delay(10);
  }
}

double readF() {
  // basic readout test, just print the current temp
   Serial.print("Internal Temp = ");
   Serial.println(thermocouple.readInternal());

   double f = thermocouple.readFahrenheit();
   if (isnan(f)) {
     Serial.println("Something wrong with thermocouple!");
     return -1;
   }

    Serial.print("F = ");
    Serial.println(f);
    return f;
}