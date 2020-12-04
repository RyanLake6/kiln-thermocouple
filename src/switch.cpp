#include <Arduino.h>

// digital IO pins for switch
#define SWITCH_PIN 14

//initialize switch
void initSwitch() {
    pinMode(SWITCH_PIN, INPUT_PULLUP);
}

bool getSwitchStatus() {
    if (digitalRead(SWITCH_PIN) == HIGH) {
        return true;
    }
    return false;
}