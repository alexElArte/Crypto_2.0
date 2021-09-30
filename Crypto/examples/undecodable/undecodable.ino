/*
 * This code show you how to combine several layer.
 * With this method you can have an undecodable message
 * You can only use encodeArray() function once per message.
 * If you use encodeArray(), you must use first.
 * You can use encodeMove() whenever you want except if you use encodeArray().
 * You must put encodeMove() after encodeArray().
 * encodeBit() is used to hide data usually after encodeArray() and encodeMove().
 * It increase the message's security.
 * You can also use mask() with a manual key instead of encodeBit
 *
 * To decode you need to use decode...() function.
 * If you began to encode with mask(), you must finish to decode with mask
 * If you end to encode with encodeMove(), you must begin to decode with encodeMove();
 * etc
*/

/*
 * This is an example you can move/add/remove
 * some function in encode() and decode()
 * but you need to keep a miror between then
 * or else you will not be able to decode the message
*/

#include <new_crypto.h>

// You can change the value to have a powerful key
// I usually use 32 or 64
const uint8_t length_array = 16;
const uint8_t max_value = 32;

Crypto cryp(max_value, length_array);

uint8_t keyA[max_value];
uint8_t keyM[length_array];
uint8_t keyM1[length_array];
uint8_t keyMask = 0x56;
uint8_t msg[16] = {
  26, 1, 2, 3,
  4, 5, 6, 7,
  8, 9, 10, 11,
  12, 13, 14, 15
};


void setup() {
  Serial.begin(115200);
  Serial.println("Example to show you the functions");
  cryp.init(analogRead(A0));

  // Create random keys
  cryp.createArrayKey(keyA); // First layer
  cryp.createMoveKey(keyM); // Third layer
  cryp.createMoveKey(keyM1); // Sixth layer

  // Print the keys
  Serial.println("The keys:");
  Serial.print("keyA:  ");
  for (uint8_t index = 0; index < max_value; index++) {
    if(keyA[index] < 0x10) Serial.write('0');
    Serial.print(keyA[index], HEX);
    Serial.write(' ');
  }
  Serial.write('\n');
  Serial.print("keyM:  ");
  for (uint8_t index = 0; index < length_array; index++) {
    if(keyM[index] < 0x10) Serial.write('0');
    Serial.print(keyM[index], HEX);
    Serial.write(' ');
  }
  Serial.write('\n');
  Serial.print("keyM1: ");
  for (uint8_t index = 0; index < length_array; index++) {
    if(keyM1[index] < 0x10) Serial.write('0');
    Serial.print(keyM1[index], HEX);
    Serial.write(' ');
  }
  Serial.write('\n');



  Serial.println("The message:");
  Serial.print("nocode: ");
  for (uint8_t index = 0; index < length_array; index++) {
    if(msg[index] < 0x10) Serial.write('0');
    Serial.print(msg[index], HEX);
    Serial.write(' ');
  }
  Serial.write('\n');

  // Encode
  encode(); // See the function below

  Serial.print("encode: ");
  for (uint8_t index = 0; index < length_array; index++) {
    if(msg[index] < 0x10) Serial.write('0');
    Serial.print(msg[index], HEX);
    Serial.write(' ');
  }
  Serial.write('\n');

  // Decode
  decode(); // See the function below

  Serial.print("decode: ");
  for (uint8_t index = 0; index < length_array; index++) {
    if(msg[index] < 0x10) Serial.write('0');
    Serial.print(msg[index], HEX);
    Serial.write(' ');
  }
  Serial.println('\n');
}

void loop() {
  //
}

void encode() {
  cryp.encodeArray(msg, keyA); // We need to put first or remove it
  cryp.encodeBit(msg);
  cryp.encodeMove(msg, keyM);  // Third layer
  cryp.encodeBit(msg);
  cryp.mask(msg, keyMask);     // Fifth layer
  cryp.encodeMove(msg, keyM1);
  cryp.encodeBit(msg);         // Seventh layer
}

void decode() {
  // Decode in reverse
  // The start is the end and the end is the start
  cryp.decodeBit(msg);         // Seventh layer
  cryp.decodeMove(msg, keyM1);
  cryp.mask(msg, keyMask);     // Fifth layer
  cryp.decodeBit(msg);
  cryp.decodeMove(msg, keyM);  // Third layer
  cryp.decodeBit(msg);
  cryp.decodeArray(msg, keyA); // First layer
}