#include <SimpleHOTP.h>

/*
In this example we will generate a SHA1-Hash of
the String "Natural Water is only natural, because it is pure."
*/

void setup () {
  String msg = "Natural Water is only natural, because it is pure.";


  // convert to char Array
  int ml = msg.length(); // number of BYTES of the message
  // +1, because of the 0-Terminator of Strings
  char msgArray[ml+1];
  msg.toCharArray(msgArray, ml+1);

  // Multiply the number of BYTES of the message by 8,
  // so we get the number of BITS of the message
  ml *= 8;
  
  uint32_t hash[5] = {}; // This will contain the 160-bit Hash
  SimpleSHA1::generateSHA(msgArray, ml, hash);
  
  
  // output every element of the hash as the hexadecimal
  // representation. The result should be:
  // FBB35A64E3913B60DD150C0F1C218FC73B3C8BD8
  Serial.begin(9600);
  for (int i = 0; i < 5; i++) {
    Serial.print(hash[i], HEX);
  }
}



void loop () {
  
}
