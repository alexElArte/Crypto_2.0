/*
 * This code show you how to use character functions.
 * Each letter or space use 1 byte.
 * Each special character use 2 bytes.
*/

#include <new_crypto.h>

const uint8_t length_array = 16;
const uint8_t max_value = TEXT_VALUE; // It is a fix number

Crypto cryp(max_value, length_array);

char msg[14] = {
  'H', 'e', 'l', 'l', 'o', ' ',
  'W', 'o', 'r', 'l', 'd', ' ', '!', '!'
};
uint8_t msg_encode[16];


void setup() {
  Serial.begin(115200);
  Serial.println("Example to show you how to encode text");
  cryp.init(analogRead(A0));


  Serial.println("The message:");
  Serial.print("nocode: ");
  Serial.write(msg, 14);
  Serial.write('\n');

  // Encode
  encode(); // See the function below

  Serial.print("encode: ");
  for (uint8_t index = 0; index < length_array; index++) {
    if(msg_encode[index] < 0x10) Serial.write('0');
    Serial.print(msg_encode[index], HEX);
    Serial.write(' ');
  }
  Serial.write('\n');

  // Decode
  decode(); // See the function below

  Serial.print("decode: ");
  Serial.write(msg, 14);
  Serial.println('\n');

  Serial.println("Other functions:");
  Serial.print("The length we need to encode: ");
  Serial.println(cryp.countString(msg, 14));
  Serial.print("The length we need to decode: ");
  Serial.println(cryp.countArray(msg_encode, 16));
}

void loop() {
  //
}

void encode() {
  uint8_t index1 = 0;
  for (uint8_t index = 0; index < 14; index++) {
    uint8_t temp = cryp.encodeChar(msg[index]);
    msg_encode[index1] = temp;
    index1++;
    if (temp == SPECIAL_CHAR) {
      msg_encode[index1] = cryp.encodeSpecial(msg[index]);
      index1++;
    }
  }
}

void decode() {
  uint8_t index1 = 0;
  uint8_t temp = 0;
  for (uint8_t index = 0; index < 16; index++) {
    if (temp == SPECIAL_CHAR) temp = cryp.decodeSpecial(msg_encode[index]);
    else temp = cryp.decodeChar(msg_encode[index]);
    
    if (temp != SPECIAL_CHAR && temp != DATA_ERROR) {
      msg[index1] = temp;
      index1++;
    }
  }
}