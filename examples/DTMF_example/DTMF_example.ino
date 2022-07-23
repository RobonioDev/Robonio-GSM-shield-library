#include <RobonioGSM.h>
RobonioGSM Robonio;
#define PhoneNumber  "+90**********" // Write down the number of the phone that will communicate with the GSM shield, putting the country code in front of it.
#define LED_pin 13
extern SoftwareSerial SIM;

void setup() {

  digitalWrite(7, HIGH);
  delay(3000);
  digitalWrite(7, LOW);
  Robonio.start();
  delay(2000);
  Serial.begin(9600);
  delay(2000);
  Robonio.allSmsDelete  ();
  delay(2000);
  SIM.println("ATS0=1");
  delay(2000);
  SIM.println("AT+DDET=1");
  delay(2000);
  Serial.println("the system is working");
  Robonio.smsSend(PhoneNumber, "system opened.");
}

void loop() {
  String incoming = "";
  if (SIM.available()) {
    while (SIM.available()) {
      delay(13);
      char c = SIM.read();
      incoming += c;
    }
    Serial.print("incoming:"); Serial.println(incoming);
    if (incoming.indexOf("DTMF: 1") != -1) {
      Serial.println("Pressed 1, LED turned on");
      digitalWrite(LED_pin, HIGH);
      Robonio.smsSend(PhoneNumber, "LED opened");
    }
    else if (incoming.indexOf("DTMF: 0") != -1) {
      Serial.println("0 pressed, LED off");
      digitalWrite(LED_pin, LOW);
      Robonio.smsSend(PhoneNumber, "LED closed");
    }
  }
}
