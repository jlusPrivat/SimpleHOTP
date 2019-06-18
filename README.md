# SimpleHOTP
A lightweight HOTP (HMAC - Based one Time Password) Generator for Arduino.  
This library is for those, who want to save on memory and still use HOTPs, as there are no heavy
third-party dependencies included.
**Please note, that C++11 must be enabled with Arduino IDE. This is default enabled as of version 1.6.6.**

## Functionalities
*Cursively written features* are not yet implemented. Any help is welcome.
1. *Generate fast and easy a [HOTP](https://tools.ietf.org/html/rfc4226 "RFC 4226")
with the secret key and the counter value*
2. *Validate easily an entered HOTP with the secret key, the counter and
and the resync look-ahead parameter*
3. Generate Keys for use in [SHA1-HMAC](https://tools.ietf.org/html/rfc2104 "RFC 2104")
authentication
4. *Generate SHA1-HMACs*
5. Generate [SHA1 kryptographic hashes](https://tools.ietf.org/html/rfc3174 "RFC 3174")
of messages with a length of up to (2^64)-1 Bits

## Changelog
Only version changes as labeled in git are listed here.
Version numbers are [semantic](https://semver.org/ "Semantic Versioning").

## License
Developed by [Jonathan Lusky](https://jlus.de "Private website")  
See the [License information sheet](LICENSE "LICENSE")
