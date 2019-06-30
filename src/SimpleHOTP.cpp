#include "SimpleHOTP.h"


const uint32_t SimpleHOTP::pow10[10] = {1,10,100,1000,
	10000,100000,1000000,10000000,100000000,1000000000};


SimpleHOTP::SimpleHOTP (Key &key, uint64_t counter):
key(key), counter(counter) {}



uint64_t SimpleHOTP::validate (uint32_t hotp) {
	// return 0 (not validated), if in locked state
	if (isLocked())
		return 0;
	
	// validate the entered hotp
	for (uint8_t i = 0; i <= resync; i++) {
		if (generateHOTP(counter+i) == hotp) {
			counter += i+1;
			return counter;
		}
	}
	
	// register any failed attempt
	failedAttempts++;
	return 0;
}



uint64_t SimpleHOTP::validate (uint8_t *hotp) {
	uint32_t toPass = 0;
	for (uint8_t i = 0; i < digits; i++) {
		toPass += hotp[i] * pow10[digits-i-1];
	}
	return validate(toPass);
}



uint32_t SimpleHOTP::generateHOTP (uint64_t counter) {
	// step 1: generate the hmac
	// for that convert the counter to big endian, if needed
	union {
		uint64_t u64;
		uint32_t u32[2];
		uint8_t u8[8];
	} c = {counter};
	if (!SimpleHMAC::isBigEndian()) {
		c.u32[0] = SimpleHMAC::convertBigEndian32(counter >> 32);
		c.u32[1] = SimpleHMAC::convertBigEndian32((uint32_t) counter);
	}
	
	// now generate the hmac
	union {uint32_t u32[5]; uint8_t u8[20];} hmac = {0};
	SimpleHMAC::generateHMAC(key, c.u8, 64, hmac.u32);
	
	// step 2: generate the 4 byte dynamic truncation string
	uint8_t offset = hmac.u32[4] & 0xF;
	uint32_t dt = 0;
	// convert to Big Endian, if necessary
	for (uint8_t i = 0; i < 5; i++)
		hmac.u32[i] = SimpleHMAC::convertBigEndian32(hmac.u32[i]);
	// generate result
	for (uint8_t i = 0; i < 4; i++)
		dt |= ((uint32_t) hmac.u8[offset+i]) << ((3-i)*8);
	// only use last 31 bits
	dt &= 0x7FFFFFFF;
	
	// step 3: generate the final hotp value
	return dt % pow10[digits];
}



uint32_t SimpleHOTP::generateHOTP () {
	return generateHOTP(counter);
}



void SimpleHOTP::setResync (uint8_t resync) {
	this->resync = resync;
}



void SimpleHOTP::setDigits (uint8_t digits) {
	if (digits >= 6 && digits <= 9)
		this->digits = digits;
}



void SimpleHOTP::setThrottle (uint8_t throttle) {
	this->throttle = throttle;
}



void SimpleHOTP::resetFailedAttempts () {
	failedAttempts = 0;
}



bool SimpleHOTP::isLocked () {
	return throttle && (throttle <= failedAttempts);
}
