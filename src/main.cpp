#include "corner.hpp"

Corner corner;

void setup() {
  Serial.begin(115200);
  Serial.println("Hello World");
  corner.setup();
}

void loop() {
  // put your main code here, to run repeatedly:
  corner.loop();
  delay(50);
}
