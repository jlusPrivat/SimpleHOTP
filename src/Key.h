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

#ifndef Key_h
#define Key_h

#include "Arduino.h"

class Key {
	private:
		uint8_t key[64] = {};
		size_t size = 0; // in Bytes
	
	
	public:
		/* Constructor for generating a new key with 64 random Bytes.
		 * This constructor uses the Arduino random() function,
		 * meaning it is advised to set the seed prior to using
		 * this constructor. Check the Arduino language reference
		 * for function randomSeed().
		 */
		Key ();
		
		
		/* Constructor for generating a new Key with random values.
		 * This constructor uses the Arduino random() function,
		 * meaning it is advised to set the seed prior to using
		 * this constructor. Check the Arduino language reference
		 * for function randomSeed().
		 *
		 * Param generationSize: the number of bytes to generate.
		 *                       When used with HMAC it is a great idea
		 *                       to set this value to 64. Max value is 64.
		 */
		Key (uint8_t generationSize);
		
		
		/* Constructor for importing a Key Array (Array of Bytes)
		 *
		 * Param importVal: The Array of values to import. Maximally 64 Bytes
		 *                  will be imported.
		 * Param importSize: the number of bytes to import.
		 */
		Key (uint8_t *importVal, uint8_t importSize);
		
		
		/* get the size of the Key
		 *
		 * Returns: the size of the Key (in Bytes)
		 */
		size_t getSize ();
		
		
		/* export the Keys value to an array. This array may be used for storage
		 * and later import back to a Key.
		 *
		 * Param expArray: Pointer to an array, which is at least as big as getSize() returns.
		 */
		void exportToArray (uint8_t *expArray);
};

#endif