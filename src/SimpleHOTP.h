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

#ifndef SimpleHOTP_h
#define SimpleHOTP_h

#include "Arduino.h"
#include "SimpleSHA1.h"
#include "Key.h"
#include "SimpleHMAC.h"


class SimpleHOTP {
	private:
		Key &key;
		uint64_t counter;
		uint8_t resync = 2;
		uint8_t digits = 6; // allowed between 6 and 9
		uint8_t throttle = 3;
		uint8_t failedAttempts = 0;
		
		uint32_t generateHOTP (uint64_t);
		
		static const uint32_t pow10[10];
	
	public:
		/* the only constructor for SimpleHOTP for use
		 * in hotp generation and validation
		 *
		 * Param key: the Key (see Key.h and matching examples
		 *            included in this library) for use in
		 *            the hotp generation and validation
		 * Param counter: the 64-bit unsigned counter value for
		 *                the next upcoming HOTP generation.
		 *                Please note that it is highly advisable
		 *                to use the return value of the validate
		 *                function to get the new counter after a
		 *                successfull validation.
		 */
		SimpleHOTP (Key &key, uint64_t counter);
		
		
		/* validates a user provided hotp against the counter,
		 * Key and resync lookahead window. Internally increments
		 * the counter, when correct hotp was provided. Internally
		 * increments failedAttempts, when wrong hotp was
		 * provided. Always returns '0', when isLocked() returns
		 * true.
		 *
		 * Param hotp: the user provided hotp as a
		 *             32 bitunsigned integer or array pointer of
		 *             8 bit unsigned integers, each containing
		 *             one digit of the HOTP (in most
		 *             significant digit first)
		 * Returns: the new counter value to store locally
		 *          or '0', if provided hotp was wrong
		 */
		uint64_t validate (uint32_t hotp);
		uint64_t validate (uint8_t *hotp);
		
		
		/* generates a single HOTP based on the counter value
		 * and the Key passed upon initialization
		 *
		 * Returns: the integer representing the HOTP.
		 */
		uint32_t generateHOTP ();
		
		
		/* sets the resync parameter, which determines how many
		 * HOTPs in advance of the current counter will be
		 * checked against a HOTP to be validated. This
		 * value should not exceed 4. Default value is 2 (so
		 * in total 3 values will be checked against any
		 * entered HOTP).
		 *
		 * Param resync: as described above, an 8-bit integer
		 */
		void setResync (uint8_t resync);
		
		
		/* sets the number of decimal digits to be used for
		 * hotp generation and validation. This library
		 * supports any value between and including 6 and 9.
		 * Default is value 6.
		 *
		 * Param digits: as described above, 8-bit integer
		 */
		void setDigits (uint8_t digits);
		
		
		/* sets the throttling parameter which determines,
		 * how many consecutive failed attempts lead to
		 * a locked state in the validation process
		 * (any input will result in being rejected).
		 * The locked state can be detected using the method
		 * isLocked() and can be reset by
		 * using resetFailedAttempts().
		 *
		 * Param throttle: as described above, 8-bit integer.
		 *                 If throttle is defined as '0'
		 *                 the device will never enter the locked
		 *                 state. Default is value 3.
		 */
		void setThrottle (uint8_t throttle);
		
		
		/* resets the counter for consecutive failed attempts.
		 * This action also releases the validation process
		 * from the locked state, in which it regardless
		 * of the user input returns '0' (false).
		 */
		void resetFailedAttempts ();
		
		
		/* Returns: true, if the validation process is in
		 *          locked state, meaning it will return false
		 *          regardless of user input. This is caused
		 *          by too many consecutive wrong user inputs.
		 *          It is advised for using another means of
		 *          authentication, once this state was reached.
		 *          It is also advised to not allow the user
		 *          to input another HOTP after a device restart
		 */
		bool isLocked ();
};


#endif
