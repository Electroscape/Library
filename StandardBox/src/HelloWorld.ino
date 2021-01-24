#include <StandardBox.h>

// I2C ADRESSES
#define RELAY_I2C_ADD     	 0x3F         // Relay Expander
#define OLED_I2C_ADD         0x3C         // Predefined by hardware
#define LCD_I2C_ADD					 0x27         // Predefined by hardware
#define KEYPAD_I2C_ADD       0x38         // Fusebox door
#define INPUT_I2C_ADD         0x39         // Fuses

bool doorClosed = false;
bool gameEnd    = false;

//Serial.println("IN");
STB_Board InExpander;
InputPin switchBtn1;
InputPin switchBtn2;
InputPin switchBtn3;
InputPin switchBtn4;

//Serial.println("OUT");

STB_Board outExpander;
OutputPin relay1;
OutputPin relay2;
OutputPin relay3;
OutputPin relay4;


void setup() {
  Serial.begin(115200);
  Serial.println("Setup");

  uint8_t exp1,exp2;
  exp1 = InExpander.Expander_init(INPUT_I2C_ADD);
  switchBtn1.init(INPUT_1_PIN, exp1);
  switchBtn2.init(INPUT_2_PIN, exp1);
  switchBtn3.init(INPUT_3_PIN, exp1);
  switchBtn4.init(INPUT_4_PIN, exp1);


  Serial.println("Relays");
  exp2 = outExpander.Expander_init(RELAY_I2C_ADD);
  relay1.init(REL_1_PIN, exp2);
  relay2.init(REL_2_PIN, exp2);
  relay3.init(REL_3_PIN, exp2);
  relay4.init(REL_4_PIN, exp2);

  Serial.println("Done");
}

void loop() {
  if (switchBtn1.read())
    {Serial.print("0");
    relay1.on();
}  else
    {Serial.print("1");
    relay1.off();}

  if (switchBtn2.read())
    {Serial.print("0");
    relay2.on();}
  else
    {Serial.print("1");
    relay2.off();}

  if (switchBtn3.read())
    {Serial.print("0");
    relay3.on();
}  else
    {Serial.print("1");
    relay3.off();}

  if (switchBtn4.read())
    {Serial.print("0");
    relay4.on();
}  else
    {Serial.print("1");
    relay4.off();}

  delay(2000);
  Serial.println();
}
