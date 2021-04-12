#include <stb_namespace.h>
using namespace stb_namespace;

stb_namespace::Brain::Brain(String BrainName) {
}

stb_namespace::Brain::~Brain() {
}

bool stb_namespace::brainSerialInit() {
    Wire.begin();
    Serial.begin(115200);
    delay(100);
    // initialize the read pin as an output:
    pinMode(MAX_CTRL_PIN, OUTPUT);
    // Welcome Print
    printWithHeader("!Setup Begin", "SYS");
    return true;
}

void stb_namespace::printWithHeader(String message, String source) {
    digitalWrite(MAX_CTRL_PIN, MAX485_WRITE);
    Serial.println();
    Serial.print("!Br,");
    Serial.print(source);
    Serial.print(",");
    Serial.print(message);
    Serial.println(",Done.");
    delay(50);
    digitalWrite(MAX_CTRL_PIN, MAX485_READ);
}


/*
void stb_namespace::heartbeat() {
    if (millis() - lastHeartbeat >= heartbeatFrequency) {
        printWithHeader(F("Hearthbeat"), F("SYS"));
    }
}
*/

void stb_namespace::softwareReset() {
    Serial.println(F("Restarting in"));
    delay(50);
    for (byte i = 3; i > 0; i--) {
        Serial.println(i);
        delay(100);
    }
    asm volatile("  jmp 0");
}

bool stb_namespace::i2cScanner() {
    Serial.println();
    Serial.println(F("I2C scanner:"));
    Serial.println(F("Scanning..."));
    byte count = 0;
    for (byte i = 8; i < 120; i++) {
        Wire.beginTransmission(i);
        if (Wire.endTransmission() == 0) {
            Serial.print("Found address: ");
            Serial.print(i, DEC);
            Serial.print(" (0x");
            Serial.print(i, HEX);
            Serial.println(")");
            count++;
            delay(1);  // maybe unneeded?
        }              // end of good response
    }                  // end of for loop
    Serial.println("Done.");
    Serial.print("Found ");
    Serial.print(count, DEC);
    Serial.println(" device(s).");

    return true;
}
