#include <SoftwareSerial.h>
SoftwareSerial Robonio(10, 11); // RX, TX

void setup() {
 /*
  digitalWrite(7, HIGH);
  delay(3000);
  digitalWrite(7, LOW);
 */
 // Delete the " /* and */ " above to automatically start the GSM shield
  Serial.begin(9600);
  Robonio.begin(9600);
}

void loop() {
  if (Robonio.available()) {
    Serial.write(Robonio.read());
  }
  if (Serial.available()) {
    Robonio.write(Serial.read());
  }
}
