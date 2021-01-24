

// OLED
#include "SSD1306Ascii.h"             /* https://github.com/greiman/SSD1306Ascii                            */
#include "SSD1306AsciiWire.h"         /* https://github.com/greiman/SSD1306Ascii                            */


// == Constructors

SSD1306AsciiWire oled;

/*==DEFINES==================================================================================================*/

// INPUT
enum INPUT_PIN{
    INPUT_1_PIN,                             //  0
    INPUT_2_PIN,                             //  1
    INPUT_3_PIN,                             //  2
    INPUT_4_PIN,                             //  3
    INPUT_5_PIN,                             //  4
    INPUT_6_PIN,                             //  5
    INPUT_7_PIN,                             //  6
    INPUT_8_PIN
};

// PWMS
enum PWM_PIN{
    PWM_1_PIN = 3,                           // Predefined by STB design
    PWM_2_PIN = 5,                           // Predefined by STB design
    PWM_3_PIN = 6,                           // Predefined by STB design
    PWM_4_PIN = 9,                           // Predefined by STB design
};


#define ON_BOARD_LED_PIN    13           // onBoardLED
#define RELAY_I2C_ADD     	0x3F         // Relay Expander
#define OLED_I2C_ADD        0x3C         // Predefined by hardware
#define LCD_I2C_ADD         0x27         // Predefined by hardware

// RELAY
// PIN
enum REL_PIN{
    REL_1_PIN ,                              // 0 Door Opener
    REL_2_PIN ,                              // 1 Buzzer
    REL_3_PIN ,                              // 2
    REL_4_PIN ,                              // 3
    REL_5_PIN ,                              // 4
    REL_6_PIN ,                              // 5
    REL_7_PIN ,                              // 6
    REL_8_PIN ,                              // 7
    REL_9_PIN ,                              // 8
    REL_10_PIN,                              // 9
    REL_11_PIN,                              // 10
    REL_12_PIN,                              // 11
    REL_13_PIN,                              // 12
    REL_14_PIN,                              // 13
    REL_15_PIN,                              // 14
    REL_16_PIN                               // 15
};

// INPUT
enum INPUT_PIN{
    INPUT_1_PIN,                             //  0 Phone pickup button
    INPUT_2_PIN,                             //  1 Coin Detector
    INPUT_3_PIN,                             //  2
    INPUT_4_PIN,                             //  3
    INPUT_5_PIN,                             //  4
    INPUT_6_PIN,                             //  5
    INPUT_7_PIN,                             //  6
    INPUT_8_PIN
};

// == constants

const enum REL_PIN relayPinArray[]  = {REL_1_PIN, REL_2_PIN, REL_3_PIN, REL_4_PIN, REL_5_PIN, REL_6_PIN, REL_7_PIN, REL_8_PIN, REL_9_PIN, REL_10_PIN, REL_11_PIN, REL_12_PIN, REL_13_PIN, REL_14_PIN, REL_15_PIN, REL_16_PIN};
const byte relayInitArray[] = {REL_1_INIT, REL_2_INIT, REL_3_INIT, REL_4_INIT, REL_5_INIT, REL_6_INIT, REL_7_INIT, REL_8_INIT, REL_9_INIT, REL_10_INIT, REL_11_INIT, REL_12_INIT, REL_13_INIT, REL_14_INIT, REL_15_INIT, REL_16_INIT};

const enum INPUT_PIN inputPinArray[]   = {INPUT_1_PIN, INPUT_2_PIN, INPUT_3_PIN, INPUT_4_PIN, INPUT_5_PIN, INPUT_6_PIN, INPUT_7_PIN};

String title = "Standarcode Example";
String versionDate = "42.2.4242";
String version = "version 0.0";

/*==FUNCTIONS==================================================================================================*/

// TODO: handling of missing defines and creation of snippets

void dbg_println(String print_dbg) {
    Serial.println(print_dbg);
    Oled.println(print_dbg);
}

void print_logo_infos(String progTitle) {
    Serial.println(F("+-----------------------------------+"));
    Serial.println(F("|    TeamEscape HH&S ENGINEERING    |"));
    Serial.println(F("+-----------------------------------+"));
    Serial.println();
    Serial.println(progTitle);
    Serial.println();
    delay(200);
}

void print_serial_header() {
    Serial.begin(115200);
    print_logo_infos(title);

    dbg_println("!header_begin");
    dbg_println(title);
    dbg_println(versionDate);
    dbg_println(version);
}

void OLED_Init() {
    Wire.begin();

    oled.begin(&Adafruit128x64, OLED_I2C_ADD);
    oled.set400kHz();
    oled.setScroll(true);
    oled.setFont(System5x7);
}

void dbg_init() {
    Serial.begin(115200);
    OLED_Init();
    print_serial_header()
}


void blink_onBoardled(uint8_t delay_ms){
	pinMode(ON_BOARD_LED_PIN, OUTPUT);
	digitalWrite(ON_BOARD_LED_PIN, HIGH);
	delay(delay_ms);
	digitalWrite(ON_BOARD_LED_PIN, LOW);
	delay(delay_ms);
	digitalWrite(ON_BOARD_LED_PIN, HIGH);
	delay(delay_ms);
	digitalWrite(ON_BOARD_LED_PIN, LOW);
}

void print_setup_end() {
    Serial.println("!setup_end");
    Serial.println(); Serial.println("===================START====================="); Serial.println();
    blink_onBoardled(100);
}


bool relay_Init() {
    Serial.println("initializing relay");
    relay.begin(RELAY_I2C_ADD);
    delay(100);
    for (int i=0; i<REL_AMOUNT; i++) {
        relay.pinMode(i, OUTPUT);
        relay.digitalWrite(i, HIGH);
        delay(100);
    }

    delay(500);

    for (int i=0; i<REL_AMOUNT; i++) {
    relay.digitalWrite(relayPinArray[i], relayInitArray[i]);
    Serial.print("     ");
    Serial.print("Relay ["); Serial.print(relayPinArray[i]); Serial.print("] set to "); Serial.println(relayInitArray[i]);
    delay(20);
    }

    Serial.println();

    Serial.println("successfully initialized relay");
    return true;
}


void i2c_scanner() {
    Serial.println (F("I2C scanner:"));
    Serial.println (F("Scanning..."));
    byte wire_device_count = 0;

    for (byte i = 8; i < 120; i++) {
        Wire.beginTransmission (i);
        if (Wire.endTransmission () == 0) {
            Serial.print   (F("Found address: "));
            Serial.print   (i, DEC);
            Serial.print   (F(" (0x"));
            Serial.print   (i, HEX);
            Serial.print (F(")"));
            if (i == 39) Serial.print(F(" -> LCD"));
            if (i == 56) Serial.print(F(" -> LCD-I2C-Board"));
            if (i == 57) Serial.print(F(" -> Input-I2C-board"));
            if (i == 60) Serial.print(F(" -> Display"));
            if (i == 63) Serial.print(F(" -> Relay"));
            if (i == 22) Serial.print(F(" -> Servo-I2C-Board"));
            Serial.println();
            wire_device_count++;
            delay (1);
        }
    }
    Serial.print   (F("Found "));
    Serial.print   (wire_device_count, DEC);
    Serial.println (F(" device(s)."));
    Serial.println("successfully scanned I2C");

    Serial.println();

    delay(500);
}

void software_Reset() {
    Serial.println(F("Restarting in"));
    delay(250);
    for (byte i = 3; i>0; i--) {
        Serial.println(i);
        delay(100);
    }
    asm volatile ("  jmp 0");
}
