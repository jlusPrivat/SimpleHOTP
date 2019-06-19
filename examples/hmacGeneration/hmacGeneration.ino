#include <SimpleHOTP.h>


void setup () {
  // this array will contain the final hmac
  uint32_t code[5];

  // import the key
  char keyVal[] = "secret passphrase";
  Key key(keyVal, sizeof(keyVal)-1);

  // generate the hmac
  char msg[] = "This is a test for hmac generation!";
  SimpleHMAC::generateHMAC(key, msg, (sizeof(msg)-1)*8, code);

  // print out the HMAC
  Serial.begin(9600);
  for (int i = 0; i < 5; i++) {
    Serial.print(code[i], HEX);
    Serial.print(" ");
  }
  
  // should output:
  // 40322845 BBB9E97C 6D23ECFA 275581DF 4143C5A2
}


void loop () {
  
}
