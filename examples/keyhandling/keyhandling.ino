#include <SimpleHOTP.h>


// this functions prints the keys to the serial monitor
void displayKey (Key &key) {
  // do not get confused, as why I am using "Key &key"
  // in this functions signature. If you really want to
  // know, go ahead and google for
  // "c++ passing objects as references"

  // export the key
  uint8_t tmp[key.getSize()];
  key.exportToArray(tmp);

  // print the exported array
  for (int i = 0; i < key.getSize(); i++) {
    Serial.print(tmp[i], HEX);
  }

  // add a new line at the end
  Serial.println();
}


void setup () {
  // A Key can be used to generate or validate a HOTP
  // and can store up to maximally 64 bytes.
  
  // There are 3 ways to initialize a Key:

  // First: Because we do not only import keys, but
  // we also let them randomly generated, we should
  // set a random seed
  randomSeed(analogRead(A0));

  // 1. (prefered)
  // generate a new Key named "secret1" with 64 bytes
  Key secret1;

  // 2.
  // generate a new Key named "secret2" with 32 bytes
  Key secret2(32);

  // 3.
  // import an exisiting key to Key named "secret3" (4 bytes)
  uint8_t toImport[] = {0xAA, 0x55, 0x10, 0xFF};
  Key secret3(toImport, 4);


  // Next we will display all keys:
  Serial.begin(9600);
  displayKey(secret1);
  displayKey(secret2);
  displayKey(secret3);
}


void loop () {
  
}
