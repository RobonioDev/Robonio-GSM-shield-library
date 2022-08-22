#include <RobonioGSM.h>
RobonioGSM Robonio;
String smsText, smsNumber;
#define PhoneNumber  "+90**********" //  Write down the number of the phone that will communicate with the GSM shield, putting the country code in front of it.
#define role1 2
#define role2 3

void setup() {
  pinMode(7 ,OUTPUT);
  digitalWrite(7, HIGH);
  delay(3000);
  digitalWrite(7, LOW);
  pinMode(role1, OUTPUT);
  pinMode(role2, OUTPUT);
  digitalWrite(role1, HIGH);
  digitalWrite(role2, HIGH);
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

      if (smsText.indexOf("RELAY1OPEN") != -1) {
        Serial.println("RELAY 1 OPENED");
        digitalWrite(role1, !HIGH);
        Robonio.smsSend(PhoneNumber, "RELAY 1 OPENED");
      }
      else if (smsText.indexOf("RELAY1CLOSE") != -1) {
        Serial.println("RELAY 1 CLOSED");
        digitalWrite(role1, !LOW);
        Robonio.smsSend(PhoneNumber, "RELAY 1 CLOSED");
      }

      else if (smsText.indexOf("RELAY2OPEN") != -1) {
        Serial.println("RELAY 2 OPENED");
        digitalWrite(role2, !HIGH);
        Robonio.smsSend(PhoneNumber, "RELAY 2 OPENED");
      }
      else if (smsText.indexOf("RELAY2CLOSE") != -1) {
        Serial.println("RELAY 2 CLOSED");
        digitalWrite(role2, !LOW);
        Robonio.smsSend(PhoneNumber, "RELAY 2 CLOSED");
      }

      else {
        Serial.println("Unidentified SMS............");
      }
      Robonio.allSmsDelete();
    }
  }
}
