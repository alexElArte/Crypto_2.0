/*
 * This code show you how to use character functions.
 * Each letter or space use 1 byte.
 * Each special character use 2 bytes.
*/

// Code to do
#if 0
#include <new_crypto.h>

const uint8_t length_array = 32;
const uint8_t max_value = TEXT_VALUE; // It is a fix number

Crypto cryp(max_value, length_array);

char msg[64];
uint8_t msg_encode[32];
uint8_t cur_index = 0;



void setup() {
  Serial.begin(115200);
  Serial.println("Example to show you how to encode text with the library");
  Serial.println("Enter text in the Serial input");
  Serial.println("Add '#' if you want to finish the sentence")
  cryp.init(analogRead(A0));
}

void loop() {
  if ()
  delay(10);
}
#endif