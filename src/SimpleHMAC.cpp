#include "SimpleHMAC.h"

void SimpleHMAC::generateHMAC (Key &key, uint8_t *message,
				   uint64_t ml, uint32_t *returner) {
	// allocate memory for the arrays
	const uint64_t innerMessageLength = 64+(ml/8)+((ml%8)==0?0:1);
	uint8_t innerMessage[innerMessageLength] = {};
	union {uint8_t u8[84]; uint32_t u32[21];} outerMessage = {};
	
	// get the key:
	key.exportToArray(innerMessage);
	key.exportToArray(outerMessage.u8);
	
	for (size_t i = 0; (i<innerMessageLength) || (i<64); i++) {
		// pad the key
		if (i < 64) {
			innerMessage[i] ^= 0x36;
			outerMessage.u8[i] ^= 0x5C;
		}
		// append the text
		else
			innerMessage[i] = message[i-64];
	}
	
	// run the inner SHA and append to outerMessage
	SimpleSHA1::generateSHA(innerMessage, ml+512, &outerMessage.u32[16]);
	
	// union: convert the 32-bit value to big endian
	for (uint8_t i = 16; i < 21; i++)
		outerMessage.u32[i] = convertBigEndian32(outerMessage.u32[i]);
	
	// now run the outer SHA
	SimpleSHA1::generateSHA(outerMessage.u8, 672, returner);
}



bool SimpleHMAC::isBigEndian () {
	union {
		uint32_t integer;
		uint8_t byde[4];
	} check = {0xAA000000};
	return check.byde[0] == 0xAA;
}



uint32_t SimpleHMAC::convertBigEndian32 (uint32_t toConvert) {
	// it is big-Endian already
	if (isBigEndian())
		return toConvert;
	
	union ConversionHelper {
		uint32_t integer;
		uint8_t byde[4];
	};
	
	// convert to big-Endian
	ConversionHelper input = {toConvert};
	ConversionHelper output = {0};
	for (uint8_t i = 0; i < 4; i++) {
		output.byde[i] = (uint8_t) input.byde[3-i];
	}
	return output.integer;
}
