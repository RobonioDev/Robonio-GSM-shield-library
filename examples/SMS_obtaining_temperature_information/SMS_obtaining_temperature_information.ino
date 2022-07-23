#include <RobonioGSM.h>
RobonioGSM Robonio;
String smsText, smsNumber;
#define PhoneNumber  "+90**********" //  Write down the number of the phone that will communicate with the GSM shield, putting the country code in front of it.
#define LM35_pin A0

void setup() {
 /*
  digitalWrite(7, HIGH);
  delay(3000);
  digitalWrite(7, LOW);
 */
 // Delete the " /* and */ " above to automatically start the GSM shield
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

      if (smsText.indexOf("temperature?") != -1) {
        Serial.println("SMS arrived");
        String temperature = String(analogRead(LM35_pin) * 0.48828125);
        String temperature2 = temperature + " degree.";
        char temperatureSMS2[] = "";
        temperature2.toCharArray(temperatureSMS2, 30);
        Serial.println(temperatureSMS2);
        Robonio.smsSend(PhoneNumber, temperatureSMS2);
      }
      else {
        Serial.println("Unidentified SMS............");
      }
      Robonio.allSmsDelete();
    }
  }
}
