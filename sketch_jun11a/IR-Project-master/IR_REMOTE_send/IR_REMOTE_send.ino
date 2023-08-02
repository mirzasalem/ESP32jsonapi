
#include <IRremote.h>

IRsend irsend=32;

void setup() {
  Serial.begin(115200);
}

void loop() {
  delay(10000);
  //Power//
  irsend.sendNEC(0xE0E06798, 2); //Power Code
  Serial.println("Power");
  delay(1000);
  //Volume Up//
  for (int i = 0; i < 10; i++) {
    irsend.sendNEC(0xE0E0E01F, 2); //Volume Up Code
    Serial.println("Volume Up");
    delay(250);
  }
  delay(5000);
  //Volume Down//
  for (int i = 0; i < 10; i++) {
    irsend.sendNEC(0xE0E0D02F, 2); //Volume Down Code
    Serial.println("Volume Down");
    delay(250);
  }
  delay(1000);
  //Netflix//
  irsend.sendNEC(0xE0E0CF30, 2); //Netflix Code
  Serial.println("Netflix");
  delay(1000);
}


