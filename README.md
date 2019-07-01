# SimpleHOTP
A lightweight HOTP (HMAC - Based one Time Password) Generator for Arduino.  
This library is for those, who want to save on memory and still use HOTPs, as there are no heavy
third-party dependencies included.

**Please note, that C++11 must be enabled with Arduino IDE. This is enabled by default as of version 1.6.6.**

## Functionalities
Anyone is welcome to add to the functionalities and report on any issues.
1. Generate fast and easy a [HOTP](https://tools.ietf.org/html/rfc4226 "RFC 4226")
with the secret key and the counter value
2. Validate easily an entered HOTP with the secret key, the counter and
and the resync look-ahead parameter
3. Generate Keys for use in [SHA1-HMAC](https://tools.ietf.org/html/rfc2104 "RFC 2104")
authentication
4. Generate SHA1-HMACs
5. Generate [SHA1 kryptographic hashes](https://tools.ietf.org/html/rfc3174 "RFC 3174")
of messages with a length of up to (2^64)-1 Bits

## Usage
It can be as easy as this validation of a user provided hotp.
```cpp
#include <SimpleHOTP.h>
int currentCounter = 3;

// ...

// load the key and the HOTP object
char secret[] = "secret passphrase";
Key key(secret, sizeof(secret)-1);
SimpleHOTP hotp(key, currentCounter);

int nextCounter = 0;
do {
    // getUserInput() as placeholder for your function!
    // it MUST return a 32-bit integer.
    nextCounter = hotp.validate(getUserInput());
} while (!nextCounter && !hotp.isLocked());

if (nextCounter) {
    // success
}
else {
    // failure
}
```
For more information on the usage please refer to the `.h` files in the `/src` directory.

## Changelog
Only version changes as labeled in git are listed here.
Version numbers are [semantic](https://semver.org/ "Semantic Versioning").

### 1.0.1
README.md fixed for reference to documentation.

## License
Developed by [Jonathan Lusky](https://jlus.de "Private website")  
See the [License information sheet](LICENSE "LICENSE")
