/*
Simple HOTP
by JONATHAN LUSKY (https://jlus.de)
This work is licensed under the MIT License

For information on the usage and the currently used
version please check the README.md.

For information on the current version, eventual issues and more, please
check the GitHub repository for this project!
https://github.com/jlusPrivat/SimpleHOTP
*/

#ifndef SimpleHMAC_h
#define SimpleHMAC_h

#include "Arduino.h"
#include "Key.h"
#include "SimpleSHA1.h"


namespace SimpleHMAC {
	/* generates a Hashed-Key Message Authentication Code
	 * with SHA1 for any message with a maximum length
	 * of (2^64)-1 bits
	 *
	 * Param key: the Key to use
	 * Param message: the array of bytes of the message
	 * Param ml: the length of the message in bits
	 * Param returner: an empty 160-Bit (5 Elements of 32 bits) for the result
	 */
	void generateHMAC (Key &key, uint8_t *message, uint64_t ml, uint32_t *returner);
	
	
	/* Returns: true, if machine has Big Endianness; false otherwise
	 */
	bool isBigEndian ();
	
	
	/* converts a number from little to big endian, if machine is little endian
	 *
	 * Param toConvert: the 32-bit value to convert to big endian
	 * Returns: the converted 32-bit value
	 */
	uint32_t convertBigEndian32 (uint32_t toConvert);
}


#endif
