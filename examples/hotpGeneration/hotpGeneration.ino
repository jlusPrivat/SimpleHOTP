#include <SimpleHOTP.h>

void setup () {
  // load the key
  char secret[] = "secret passphrase";
  Key key(secret, sizeof(secret)-1);

  // generate the hotp value
  SimpleHOTP gen(key, 3);
  uint32_t hotp = gen.generateHOTP();

  // print the value:
  Serial.begin(9600);
  Serial.print("HOTP for count 3: ");
  Serial.println(hotp);

  // should output 599762
}


void loop () {
  
}
