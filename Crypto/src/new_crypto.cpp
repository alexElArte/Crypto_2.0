/*
	Crypto.h - Library for flashing cryptography code.
	Created by Alexandre.M, May 25, 2021.
	Released into the public domain.
*/

#include "new_crypto.h"

/*
 * Init the class in the sketch
 * @param maxValue  maximum value you can put in an array
 * @param lenArray  length of the input array
*/
Crypto::Crypto(uint8_t maxValue, uint8_t lenArray) {
	// Something we do when the class is called
	_maxValue = maxValue;
	_lenArray = lenArray;
}

/*
 * Init the class in the program
 * @param seed    init random to create keys
*/
void Crypto::init(long seed) {
	randomSeed(seed);
}

/*
 * Encode an array by modify each byte by a key number
 * Note that the interval is [1;maxValue], 0 is a null data
 * and replace by a random number
 * @param array   the array to encode
 * @key           the key array
*/
void Crypto::encodeArray(uint8_t* array, uint8_t* key) {
	for (uint8_t index = 0; index < _lenArray; index++) {
		// Test if the data is in the interval
		if (array[index] <= _maxValue && array[index] != 0) {
			array[index] = key[array[index]-1]; // See README.md
		} else {
			// Test if the number is not a key
			for (;;) { // Faster than while
				_key = random(0xff);
				for (uint8_t j = 0; j < _maxValue; j++) {
					if (key[j] == _key) goto endEnArray; // Quit two loop
				}
			}
			endEnArray:
			array[index] = _key;
		}
	}
}

/*
 * Decode an array by modify each byte by a key number
 * Note that the interval is [1;maxValue], 0 is a null data
 * and replace by a random number
 * @param array   the array to decode
 * @key           the key array
*/
void Crypto::decodeArray(uint8_t* array, uint8_t* key) {
	for (uint8_t index = 0; index < _lenArray; index++) {
		// Search the number in the key array
		for (uint8_t j = 0; j < _maxValue; j++) {
			if (key[j] == array[index]) {
				array[index] = j + 1;
				goto endDeArray;
			}
		}
		// If no match put a null value
		array[index] = 0;
		endDeArray:;
	}
}

/*
 * Encode an array by moving each byte by in another index
 * @param array   the array to encode
 * @key           the key array
*/
void Crypto::encodeMove(uint8_t* array, uint8_t* key) {
	uint8_t temp[_lenArray];
	// Put the datas in a temporary array
	for (uint8_t index = 0; index < _lenArray; index++) {
		temp[index] = array[index];
	}
	// Move each data
	// For more information see the README file -> Move
	for (uint8_t index = 0; index < _lenArray; index++) {
		array[key[index]] = temp[index];
	}
}

/*
 * Decode an array by moving each byte by in another index
 * @param array   the array to decode
 * @key           the key array
*/
void Crypto::decodeMove(uint8_t* array, uint8_t* key) {
	uint8_t temp[_lenArray];
	// Put the datas in a temporary variable
	for (uint8_t index = 0; index < _lenArray; index++) {
		temp[index] = array[index];
	}
	// Move each
	// For more information see the README file -> Move
	for (uint8_t index = 0; index < _lenArray; index++) {
		array[index] = temp[key[index]];
	}
}

/*
 * Encode an array by adding the mask of a value to an other value
 * @param array   the array to encode
*/
void Crypto::encodeBit(uint8_t* array) {
	// For more information see the README file -> Mask
	for (uint8_t index = 1; index < _lenArray; index++) {
		array[index] ^= array[index-1];
	}
	array[0] ^= array[_lenArray-1];
}

/*
 * Decode an array by adding the mask of a value to an other value
 * @param array   the array to decode
*/
void Crypto::decodeBit(uint8_t* array) {
	// For more information see the README file -> Mask
	array[0] ^= array[_lenArray-1];
	for (uint8_t index = _lenArray-1; index > 0; index--) {
		array[index] ^= array[index-1];
	}
}

/*
 * Encode and decode an array a same mask on all the array
 * @param array   the array to encode or decode
 * @mask          the mask to applie on the array
*/
void Crypto::mask(uint8_t* array, uint8_t mask) {
	// For more information see the README file -> Mask
	for (uint8_t index = 0; index < _lenArray; index++) {
		array[index] ^= mask;
	}
}

/*
 * Create a  key array for encodeArray() / decodeArray()
 * @param key     the ouptut array for the key
*/
void Crypto::createArrayKey(uint8_t* key) {
	for (uint8_t index = 0; index < _maxValue; index++) {
		// While the key is the same as another repeat the sequence
		newLoopCrArray: // Address
		// Get a number between 0 and 255
		_key = random(256);
		// Test all variable if it is twice in the array
		for (uint8_t j = 0; j <= index; j++) {
			if (key[j] == _key) goto newLoopCrArray; // Repeat here
		}
		// Continue if no keys match
		// Put the tested number into the array
		key[index] = _key;
	}
}

/*
 * Create a  key array for encodeMove() / decodeMove()
 * @param key     the ouptut array for the key
*/
void Crypto::createMoveKey(uint8_t* key) {
	for (uint8_t index = 0; index < _lenArray; index++) {
		// While the key is the same as another repeat the sequence
		newLoopCrMove: // Address
		// Get a number between 0 and the key's length
		_key = random(_lenArray);
		// Test all variable if it is twice in the array
		for (uint8_t j = 0; j < index; j++) {
			if (key[j] == _key) goto newLoopCrMove; // Repeat here
		}
		// Continue if no keys match
		// Put the tested number into the array
		key[index] = _key;
	}
}

/*
 * Encode simple characters in range from 1 to 64
 * 64 is say to look in the other table: encodeSpecial()
 * @param data    the data to tranform
 * @return a number from 1 to 64
*/
uint8_t Crypto::encodeChar(char data) {
	// Test all possibilities
	// I add +1 to have the value between 1 and 64
	// Remember 0 is a null value and replace by a random number
	/*                                                      value  char    offset*/
	if (data >= '0' && data <= '9') return (data - '0') + 2;
	else if (data >= 'A' && data <= 'Z') return (data - 'A') + 12;
	else if (data >= 'a' && data <= 'z') return (data -'a') + 38;
	else if (data == ' ') return 64; // space
	return 1; // Other data
}

/*
 * Encode special charaters (see README)
 * @param data    the data to transform
 * @return a number from 1 to 34 or 0xff if the data can't be encode
*/
uint8_t Crypto::encodeSpecial(char data) {
	if (data == '\0') return 2;
	else if (data == '\n') return 3;
	else if (data >= '!' && data <= '/') return (data - '!') + 4;
	else if (data >= ':' && data <= '@') return (data - ':') + 19;
	else if (data >= '[' && data <= '`') return (data - '[') + 26;
	else if (data >= '{' && data <= '~') return (data - '{') + 32;
	return 0xff; // Can't encode
}

/*
 * Decode simple characters (see README)
 * @param data    the data to transform
 * @return a character, 1 if it is a special character or 0xff if nothing
*/
char Crypto::decodeChar(uint8_t data) {
	if (data >= 2 && data <= 11) return (data + '0') - 2;
	else if (data >= 12 && data <= 37) return (data + 'A') - 12;
	else if (data >= 38 && data <= 63) return (data + 'a') - 38;
	else if (data == 64) return ' '; // space
	else if (data == 1) return 1; // Special char
	return 0xff; // Can't decode
}

/*
 * Decode special characters (see README)
 * @param data    the data to transform
 * @return a character or 0xff if nothing
*/
char Crypto::decodeSpecial(uint8_t data) {
	if (data == 2) return '\0';
	else if (data == 3) return '\n';
	else if (data >= 4 && data <= 18) return (data + '!') - 4;
	else if (data >= 19 && data <= 25) return (data + ':') - 19;
	else if (data >= 26 && data <= 31) return (data + '[') - 26;
	else if (data >= 32 && data <= 35) return (data + '{') - 32;
	return 0xff; // Can't encode
}

/*
 * Count the size of the out array
 * @param array   the input char array
 * @param size    the size of the array
 * @return the size of the encode array
*/
uint8_t Crypto::countString(char* array, uint8_t size) {
	uint8_t count = 0;
	for (uint8_t index = 0; index < size; index++) {
		if (encodeChar(array[index]) == SPECIAL_CHAR) count++;
		count++;
	}
	return count;
}


/*
 * Count the size of the out array
 * @param array   the input byte array
 * @param size    the size of the array
 * @return the size of the decode array
*/
uint8_t Crypto::countArray(uint8_t* array, uint8_t size) {
	uint8_t count = 0;
	uint8_t temp = 0;
	for (uint8_t index = 0; index < size; index++) {
		if (temp == SPECIAL_CHAR) {
			count++;
			temp = 0;
			continue;
		}
		temp = decodeChar(array[index]);
		if (temp != SPECIAL_CHAR) count++;
	}
	return count;
}

/*
 * Encode a string array
 * @param input   the input text
 * @param output  the output encode array
 * @param size    the size of the input array
 * @return 0 if finish or the index where the code stoped
*/
uint8_t Crypto::encodeString(char* input, uint8_t* output, uint8_t size) {
	uint8_t index1 = 0;
	for (uint8_t index = 0; index < size; index++) {
		uint8_t temp = encodeChar(input[index]);
		output[index1] = temp;
		index1++;
		if (index1 == _lenArray) {
			if (temp == SPECIAL_CHAR) output[index1-1] = 64; // Space
			return index + 1;
		}
		if (temp == SPECIAL_CHAR) {
			output[index1] = encodeSpecial(input[index]);
			index1++;
			if (index1 == _lenArray) return index + 1;
		}
	}
	return 0;
}

/*
 * Encode a string array
 * @param input   the input array
 * @param output  the output decode array
 * @return the size of the string
*/
uint8_t Crypto::decodeString(uint8_t* input, char* output) {
	uint8_t index1 = 0;
	uint8_t temp = 0;
	for (uint8_t index = 0; index < _lenArray; index++) {
		if (temp == SPECIAL_CHAR) temp = decodeSpecial(input[index]);
		else temp = decodeChar(input[index]);

		if (temp != SPECIAL_CHAR && temp != DATA_ERROR) {
			output[index1] = temp;
			index1++;
		}
	}
	return index1;
}