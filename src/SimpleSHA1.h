/*
Simple HOTP
by JONATHAN LUSKY (https://jlus.de)
This work is licensed under the MIT License

For information on the usage and the currently used
version please check the README.md.

For information on the current version, eventual issues and more, please
check the GitHub repository for this project!
https://github.com/jlusPrivat/SimpleHOTP

--------------------------

Simple SHA class generates a 160-bit SHA-1 Hash from an Array of 8-Bit Data
*/

#ifndef SimpleSHA1_h
#define SimpleSHA1_h

#include "Arduino.h"

namespace SimpleSHA1 {
	/* Rotates a 32-bit integer left
	 *
	 * Param input: the integer to rotate
	 * Param n: the number of places to rotate; max 32
	 * Returns: the rotated integer
	 */
	uint32_t rotL (uint32_t input, uint8_t n);
	
	
	/* Generates the Sha-1 Hash for a given message
	 * 
	 * Param message: An Array of Bytes containing the message
	 * Param ml: the length of the message (in bits)
	 * Param returner: an empty 5 element 32-bit array
	 */
	void generateSHA (uint8_t *message, uint64_t ml, uint32_t *returner);
	
}


#endif