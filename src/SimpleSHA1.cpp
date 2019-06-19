#include "SimpleSHA1.h"
#define h0 returner[0]
#define h1 returner[1]
#define h2 returner[2]
#define h3 returner[3]
#define h4 returner[4]

void SimpleSHA1::generateSHA (uint8_t *message, uint64_t ml, uint32_t *returner) {
	// initialize variables
	h0 = 0x67452301;
	h1 = 0xEFCDAB89;
	h2 = 0x98BADCFE;
	h3 = 0x10325476;
	h4 = 0xC3D2E1F0;
	
	// calculate the number of required cycles and create a blocks array
	uint32_t numCycles = ((ml+65)/512)+1;
	uint32_t blocks[numCycles*16] = {};
	
	// copy message
	uint32_t messageBytes = ml/8 + (ml%8!=0 ? 1 : 0);
	for (uint32_t i = 0; i < messageBytes; i++) {
		blocks[i/4] |= ((uint32_t) message[i]) << (8*(3-(i%4)));
	}
	
	// append the 1 bit
	blocks[ml/32] |= ((uint32_t) 0b1) << (31-(ml%32));
	
	// append the 64-bit big endian ml at the end
	if (ml < 0x80000000)
		blocks[(numCycles*16)-1] = (uint32_t) ml;
	else {
		blocks[(numCycles*16)-2] = (uint32_t) ml;
		blocks[(numCycles*16)-1] = (uint32_t) (ml >> 32);
	}
	
	for (uint32_t iCycle = 0; iCycle < numCycles; iCycle++) {
		// initalize locals
		uint32_t w[80] = {};
		uint32_t a = h0, b = h1, c = h2, d = h3, e = h4;
		
		for (uint8_t i = 0; i < 80; i++) {
			// convert words to big-endian and copy to 80-elem array
			if (i < 16)
				w[i] = blocks[(iCycle*16)+i];
			else
				w[i] = rotL((w[i-3]^w[i-8]^w[i-14]^w[i-16]), 1);
			
			// run defined formulas
			uint32_t f, k, temp;
			if (i < 20) {
				f = (b & c) | ((~b) & d);
				k = 0x5A827999;
			}
			else if (i < 40) {
				f = b ^ c ^ d;
				k = 0x6ED9EBA1;
			}
			else if (i < 60) {
				f = (b & c) | (b & d) | (c & d);
				k = 0x8F1BBCDC;
			}
			else {
				f = b ^ c ^ d;
				k = 0xCA62C1D6;
			}
			temp = rotL(a, 5) + f + e + k + w[i];
			e = d; d = c; c = rotL(b, 30); b = a; a = temp;
		}
		
		// write back the results
		h0 += a; h1 += b; h2 += c; h3 += d; h4 += e;
	}
}



uint32_t SimpleSHA1::rotL (uint32_t input, uint8_t n) {
	return (input << n) | (input >> (32-n));
}