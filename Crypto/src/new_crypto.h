/*
	Crypto.h - Library for flashing cryptography function.
	Created by alexELArte, May 25, 2021.
	Released into the public domain.
*/

#ifndef CRYPTO_H
#define CRYPTO_H

#if ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#define SPECIAL_CHAR 1
#define DATA_ERROR   0xff
#define TEXT_VALUE   64

class Crypto {
	public:
		Crypto(uint8_t maxValue, uint8_t lenArray); // Use to init the library in the sketch before the program
		void init(long seed); // Use to init the random module in the program, you can't use to create keys without it

		// Set or get the length of keys
		// You can change the value in your program but carefully.
		// Your keys and array need to match !!!
		void setMaxValue(uint8_t value) {_maxValue = value;}
		void setLengthArray(uint8_t length) {_lenArray = length;}
		uint8_t getMaxValue() {return _maxValue;}
		uint8_t getLengthArray() {return _lenArray;}

		// Encode function
		void encodeArray(uint8_t* array, uint8_t* key); // For more information see README.md -> Move (the code is barely the same)
		void encodeMove(uint8_t* array, uint8_t* key); // For more information see README.md -> Move
		void encodeBit(uint8_t* array); // For more information see README.md -> Mask

		// Decode function
		void decodeArray(uint8_t* array, uint8_t* key);
		void decodeMove(uint8_t* array, uint8_t* key);
		void decodeBit(uint8_t* array);

		// Add or remove a mask for all data
		void mask(uint8_t* array, uint8_t mask); // For more information see README.md -> Mask(Two first content)

		// Create keys
		void createArrayKey(uint8_t* key);
		void createMoveKey(uint8_t* key);

		// Encode / decode char
		uint8_t encodeChar(char data);		// For more information see README.md -> Encode/decode char
		uint8_t encodeSpecial(char data);	// For more information see README.md -> Encode/decode char
		char decodeChar(uint8_t data);		// For more information see README.md -> Encode/decode char
		char decodeSpecial(uint8_t data);	// For more information see README.md -> Encode/decode char

		// Example to do
		// Encode / decode string
		uint8_t encodeString(char* input, uint8_t* output, uint8_t size);
		uint8_t decodeString(uint8_t* input, char* output);
		uint8_t countString(char* array, uint8_t size);
		uint8_t countArray(uint8_t* array, uint8_t size);
		
	private:
		uint8_t _maxValue; // The maximum value you can put in an array
		uint8_t _lenArray; // Length of an array
		uint8_t _key;
};
#endif