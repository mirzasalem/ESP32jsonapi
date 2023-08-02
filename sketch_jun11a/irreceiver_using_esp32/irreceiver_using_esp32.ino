#include <IRremoteESP8266.h>
#include <IRrecv.h>


IRrecv irrecv(15);
decode_results results;

void setup() {
  // put your setup code here, to run once:

  irrecv.enableIRIn();
  //pinmode(ledPin, OUTPUT);
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  if(irrecv.decode(&results))
  {
    Serial.println(results.value, HEX);
    //if(result)
    delay(1000);
    irrecv.resume();
  }
      

}