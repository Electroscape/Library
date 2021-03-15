#include <stb_namespace.h>
using namespace stb_namespace;

stb_namespace::Brain::Brain(String BrainName)
{
}

stb_namespace::Brain::~Brain()
{
}

void stb_namespace::printWithHeader(String message, String source)
{
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

void stb_namespace::software_Reset()
{
  Serial.println(F("Restarting in"));
  delay(50);
  for (byte i = 3; i > 0; i--)
  {
    Serial.println(i);
    delay(100);
  }
  asm volatile("  jmp 0");
}
