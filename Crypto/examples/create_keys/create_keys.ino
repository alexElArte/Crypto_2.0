#include <new_crypto.h>

// You can change the value to have a powerful key
// I usually use 32 or 64
const uint8_t length_array = 16;
// The max value depends on the context
const uint8_t max_value = 32;

Crypto cryp(max_value, length_array);

uint8_t keyA[max_value];
uint8_t keyM[length_array];


void setup() {
  Serial.begin(115200);
  Serial.println();

  cryp.init(analogRead(A0));

  // Create two keys
  cryp.createArrayKey(keyA);
  cryp.createMoveKey(keyM);
  
  // Print them
  Serial.print("uint8_t keyA[");
  Serial.print(max_value);
  Serial.print("] = {");
  for (uint8_t index = 0; index < max_value; index++) {
    Serial.print("0x");
    Serial.print(keyA[index], HEX);
    if(index != max_value-1){
      Serial.print(", ");
    }
  }
  Serial.println("};");

  Serial.print("uint8_t keyM[");
  Serial.print(length_array);
  Serial.print("] = {");
  for (uint8_t index = 0; index < length_array; index++) {
    Serial.print("0x");
    Serial.print(keyM[index], HEX);
    if(index != length_array-1){
      Serial.print(", ");
    }
  }
  Serial.println("};");
}
void loop() {
  //
}
