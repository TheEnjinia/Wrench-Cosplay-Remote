/* @file HelloKeypad.pde
  || @version 1.0
  || @author Alexander Brevig
  || @contact alexanderbrevig@gmail.com
  ||
  || @description
  || | Demonstrates the simplest use of the matrix Keypad library.
  || #
*/
#include <Keypad.h>
#include <SoftwareSerial.h>

const byte ROWS = 5; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'0', '1', '2', '3'},
  {'4', '5', '6', '7'}, 
  {'8', '9', 'A', 'B'},
  {'C', 'D', 'E', 'F'},
  {'G', 'H', 'I', 'J'}
};
byte rowPins[ROWS] = {2, 3, 4, 5 ,6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {10, 9, 8, 7}; //connect to the column pinouts of the keypad
bool hold = 0;
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

SoftwareSerial mySerial(11, 12); // RX, TX
void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  keypad.addEventListener(keypadEvent); // Add an event listener for this keypad
}

void loop() {
  char key = keypad.getKey();

  //patching software serial to hardware serial
  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }
}


// Taking care of some special events.
void keypadEvent(KeypadEvent key) {
  switch (keypad.getState()) {
    case PRESSED:
      hold = false; 
      Serial.println(KeyToString(key));
      mySerial.println(KeyToString(key));
      break;

    case RELEASED:
      if (!hold) //only clear displays when the button is pressed quickly
      {
        Serial.println("17");
        mySerial.println("17"); //Anything above 16 will clear matrixes, ugly but it works
      }
      break;

    case HOLD:
      hold = true;
      Serial.println(KeyToString(key));
      mySerial.println(KeyToString(key)); 
      break;
  }
}


String KeyToString(char keypressed)
{
  String temp;
  switch (keypressed) {
    case 'A':
      temp = "10";
    break;
     case 'B':
      temp = "11";
    break;
    case 'C':
      temp = "12";
    break;
    case 'D':
      temp = "13";
    break;   
    case 'E':
      temp = "14";
    break;
    case 'F':
      temp = "15";
    break;   
    case 'G':
      temp = "16";
    break;   
        
    default:
      temp = keypressed;
  }

  return temp;
}
