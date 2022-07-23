#include <RobonioGSM.h>
RobonioGSM Robonio;
String smsText, smsNumber;
#define PhoneNumber  "+90**********" //  Write down the number of the phone that will communicate with the GSM shield, putting the country code in front of it.
#define sensor_pin A0 

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

      if (smsText.indexOf("WEATHER?") != -1 || smsText.indexOf("QUALITY?") != -1 || smsText.indexOf("POLLUTION?") != -1) {
        Serial.println("SMS arrived");
        String gas = String(analogRead(sensor_pin) / 10,23);
        String gas2 = "WEATHER %" + gas + " dirty.";
        char gasSMS2[] = "";
        gas2.toCharArray(gasSMS2, 30);
        Serial.println(gasSMS2);
        Robonio.smsSend(PhoneNumber, gasSMS2);
      }
      else {
        Serial.println("Unidentified SMS............");
      }
      Robonio.allSmsDelete();
    }
  }
}
