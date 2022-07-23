#include <RobonioGSM.h>
RobonioGSM Robonio;
String smsText, smsNumber;
#define PhoneNumber  "+90**********" //  Write down the number of the phone that will communicate with the GSM shield, putting the country code in front of it.
#define LED_pin 13

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
  Serial.println("the system is working");
  Robonio.smsSend(PhoneNumber, "system opened.");
}

void loop() {
  smsText = Robonio.smsRead(1);
  if (smsText.indexOf("OK") != -1) {
    if (smsText.length() > 7) {
      smsNumber = Robonio.NumberSmsRead(1);
      Serial.println(smsNumber);
      smsText.toUpperCase();
      
      if (smsText.indexOf("LEDOPEN") != -1) {
        Serial.println("LED OPENED");
        digitalWrite(LED_pin, HIGH);
        Robonio.smsSend(PhoneNumber, "LED OPENED");
      }
      else if (smsText.indexOf("LEDCLOSE") != -1) {
        Serial.println("LED CLOSED");
        digitalWrite(LED_pin, LOW);
        Robonio.smsSend(PhoneNumber, "LED CLOSED");
      }
      else {
        Serial.println("Unidentified SMS............");
      }
      Robonio.allSmsDelete();
    }
  }
}
