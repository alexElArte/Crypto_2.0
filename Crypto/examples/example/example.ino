#include <new_crypto.h>

// You can change the value to have a powerful key
// I usually use 32 or 64
const uint8_t length_array = 16;
// The max value depends on the context
const uint8_t max_value = 32;

Crypto cryp(max_value, length_array);

uint8_t keyA[max_value];
uint8_t keyM[length_array];
uint8_t msg[length_array] = {
  0, 1, 2, 3,
  4, 5, 6, 7,
  8, 9, 10, 11,
  12, 13, 14, 15
};


void setup() {
  Serial.begin(115200);
  Serial.println("Example to show you the functions\n");
  cryp.init(analogRead(A0));

  /***********************KEYM***********************/
  // Create a key
  cryp.createMoveKey(keyM);
  Serial.println("Move function:");
  Serial.print("keyM: ");
  for (uint8_t index = 0; index < length_array; index++) {
    if (keyM[index] < 0x10) Serial.write('0');
    Serial.print(keyM[index], HEX);
    Serial.write(' ');
  }
  Serial.println();

  Serial.print("nocode: ");
  for (uint8_t index = 0; index < length_array; index++) {
    if (msg[index] < 0x10) Serial.write('0');
    Serial.print(msg[index], HEX);
    Serial.write(' ');
  }
  Serial.println();

  // Encode
  cryp.encodeMove(msg, keyM);
  Serial.print("encode: ");
  for (uint8_t index = 0; index < length_array; index++) {
    if (msg[index] < 0x10) Serial.write('0');
    Serial.print(msg[index], HEX);
    Serial.write(' ');
  }
  Serial.println();

  // Decode
  cryp.decodeMove(msg, keyM);
  Serial.print("decode: ");
  for (uint8_t index = 0; index < length_array; index++) {
    if (msg[index] < 0x10) Serial.write('0');
    Serial.print(msg[index], HEX);
    Serial.write(' ');
  }
  Serial.println('\n');

  /***********************KEYC***********************/
  // Create a key
  cryp.createArrayKey(keyA);
  Serial.println("Value change function:");
  Serial.print("keyA: ");
  for (uint8_t index = 0; index < length_array; index++) {
    if (keyA[index] < 0x10) Serial.write('0');
    Serial.print(keyA[index], HEX);
    Serial.write(' ');
  }
  Serial.println();

  Serial.print("nocode: ");
  for (uint8_t index = 0; index < length_array; index++) {
    if (msg[index] < 0x10) Serial.write('0');
    Serial.print(msg[index], HEX);
    Serial.write(' ');
  }
  Serial.println();

  // Encode
  cryp.encodeArray(msg, keyA);
  Serial.print("encode: ");
  for (uint8_t index = 0; index < length_array; index++) {
    if (msg[index] < 0x10) Serial.write('0');
    Serial.print(msg[index], HEX);
    Serial.write(' ');
  }
  Serial.println();

  // Decode
  cryp.decodeArray(msg, keyA);
  Serial.print("decode: ");
  for (uint8_t index = 0; index < length_array; index++) {
    if (msg[index] < 0x10) Serial.write('0');
    Serial.print(msg[index], HEX);
    Serial.print(' ');
  }
  Serial.println("\nIf you look at the first byte, the value is different(it's normal)");
  Serial.println("because 0 is a null value and change by a random value.");
  Serial.println("So in this example the number are encoded from 1 to maxValue (here 16) include.");
  Serial.println("So be carefull !!!\n");

  /*********************NOKEY***********************/
  Serial.println("This function doesn't need any key");
  Serial.println("Mask (auto):");
  Serial.print("nocode: ");
  for (uint8_t index = 0; index < length_array; index++) {
    if (msg[index] < 0x10) Serial.write('0');
    Serial.print(msg[index], HEX);
    Serial.write(' ');
  }
  Serial.println();

  // Encode
  cryp.encodeBit(msg);
  Serial.print("encode: ");
  for (uint8_t index = 0; index < length_array; index++) {
    if (msg[index] < 0x10) Serial.write('0');
    Serial.print(msg[index], HEX);
    Serial.write(' ');
  }
  Serial.println();

  // Decode
  cryp.decodeBit(msg);
  Serial.print("decode: ");
  for (uint8_t index = 0; index < length_array; index++) {
    if (msg[index] < 0x10) Serial.write('0');
    Serial.print(msg[index], HEX);
    Serial.write(' ');
  }
  Serial.println('\n');

  /***************************************/

  Serial.println("Mask (manual) 0x37:");
  Serial.print("nocode:     ");
  for (uint8_t index = 0; index < length_array; index++) {
    if (msg[index] < 0x10) Serial.write('0');
    Serial.print(msg[index], HEX);
    Serial.write(' ');
  }
  Serial.println();

  // Encode
  cryp.mask(msg, 0x37);
  Serial.print("first time: ");
  for (uint8_t index = 0; index < length_array; index++) {
    if (msg[index] < 0x10) Serial.write('0');
    Serial.print(msg[index], HEX);
    Serial.write(' ');
  }
  Serial.println();

  // Decode
  cryp.mask(msg, 0x37);
  Serial.print("second time: ");
  for (uint8_t index = 0; index < length_array; index++) {
    if (msg[index] < 0x10) Serial.write('0');
    Serial.print(msg[index], HEX);
    Serial.write(' ');
  }
  Serial.println('\n');
}
void loop() {
  //
}
