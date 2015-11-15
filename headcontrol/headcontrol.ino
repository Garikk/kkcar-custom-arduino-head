#include <Keypad.h>
#include <Wire.h>

byte val = 0;
char HeadKey[2];

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
const String PFX_KEY="$K_";
char keys[ROWS][COLS] = {
  {'4', 'F', 'H', '5'},
  {'3', 'R', 'A', 'M'},
  {'2', 'B', 'U', 'O'},
  {'1', 'C', 'D', 'S'}
};
byte rowPins[ROWS] = {5, 6, 7, 8}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {9, 10, 11, 12}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
void receiveEvent(int howMany) {
  /*int a=0;
  while(Wire.available()>0)
  {
    Wire.read();
    a++;
  }
  Serial.print("read bytes: ");
  Serial.println(a);
  */
}

void sendData() {
  if (HeadKey[0]!='0')
  {
    Wire.write(HeadKey, 2);
    HeadKey[0]='0';
  }
}

void setup() {
  Serial.begin(9600);
  Wire.begin(0x2b); // Enable i2c
  Wire.onReceive(receiveEvent);
  Wire.onRequest(sendData);

}

void loop() {
  char key = keypad.getKey();

  if (key != NO_KEY) {
    Serial.println(PFX_KEY+key);
    
    HeadKey[0]='1';
    HeadKey[1]=key;
    //  Wire.beginTransmission(0x2c); // передача для устройства #44 (0x2c)
    // адрес устройства указывается в документации (datasheet)
    //  byte Dat[] = {1,val};         //1 - Button
    //  Wire.write(Dat,2);             // отправка байта val
    //   Wire.endTransmission();     // передача данных
  }


}
