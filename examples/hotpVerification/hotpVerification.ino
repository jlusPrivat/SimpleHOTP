#include <SimpleHOTP.h>

/* Correct input would be
599762, 317879, 421937
there are 3 because of the resync frame*/

int currentCounter = 3;

// the buffer to store the serial input in
byte userInputBuffer[6];
int userBufferI = 0;


void setup () {
  // load a given key
  char secret[] = "secret passphrase";
  Key key(secret, sizeof(secret)-1);

  // initialize an HOTP object
  SimpleHOTP hotp(key, currentCounter);

  Serial.begin(9600);
  // Either leave loop when abourted because of too many
  // false inputs or because of the correct input.
  while (true) {
    
    // Ask the user for input
    Serial.println("Please enter your HOTP!");
    
    // wait for the user input to come
    while (userBufferI < 6) {
      if (Serial.available()) {
        byte incoming = Serial.read();
        if (incoming >= 48 && incoming <= 57) {
          // subtract 48 because of the incoming ASCII-encoding
          userInputBuffer[userBufferI++] = incoming - 48;
        }
      }
    }
    userBufferI = 0;

    // simple validate
    int tmpNewCounter = hotp.validate(userInputBuffer);
    if (tmpNewCounter) {
      Serial.println("Correct!");
      break; // exit the while loop
    }
    else if (hotp.isLocked()) {
      Serial.println("Your device is locked!");
      break; // exit the while loop
    }
    else {
      Serial.println("False!\r\n");
    }
    
  }

  Serial.println("\r\nEnd of test.");
}


void loop () {
  
}
