#include "AsyncUSBSerialRK.h"

SYSTEM_THREAD(ENABLED);


void setup() {
    // Replaces: Serial.begin();
    AsyncUSBSerialRK::instance().begin();
}

void loop() {
    static unsigned long lastRun = 0;

    unsigned long start = millis();
    AsyncUSBSerialRK::instance().printlnf("test %lu", lastRun);
    lastRun = millis() - start;

    delay(1000);
}