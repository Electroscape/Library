/*
Data types
*/

// I2C ADRESSES
#define RELAY_I2C_ADD     	 0x3F         // Relay Expander
#define OLED_I2C_ADD         0x3C         // Predefined by hardware
#define LCD_I2C_ADD					 0x27         // Predefined by hardware
#define KEYPAD_I2C_ADD       0x38         // Fusebox door
#define INPUT_I2C_ADD         0x39         // Fuses


//Keypad

//LED_STRIP
#define LED_STRIP WS2812B                 // Type of LED Strip, predefined by STB design
#define MAX_DIMENSION ((kMatrixWidth>kMatrixHeight) ? kMatrixWidth : kMatrixHeight) // if w > h -> MAX_DIMENSION=kMatrixWidth, else MAX_DIMENSION=kMatrixHeight
#define NUM_LEDS (kMatrixWidth * kMatrixHeight)

// RELAYS
enum REL_PIN{
  REL_1_PIN ,                              // 0 Fusebox lid
  REL_2_PIN ,                              // 1 Door opener / Alarm light
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
enum INPUT_PINs{
  INPUT_1_PIN,                             //  0 alarm light at the entrance/exit
  INPUT_2_PIN,                             //  1 trigger for starting the procedure
  INPUT_3_PIN,                             //  2
  INPUT_4_PIN,                             //  3
  INPUT_5_PIN,                             //  4
  INPUT_6_PIN,                             //  5
  INPUT_7_PIN,                             //  6
  INPUT_8_PIN
};
