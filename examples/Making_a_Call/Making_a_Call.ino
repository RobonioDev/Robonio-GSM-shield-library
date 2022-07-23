#include <RobonioGSM.h>
RobonioGSM Robonio;
String smsText, smsNumber;
#define PhoneNumber  "+90**********" //  Write down the number of the phone that will communicate with the GSM shield, putting the country code in front of it.

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
  Serial.print(PhoneNumber);
  Serial.println(" araniyor...");
  Robonio.numberCall(PhoneNumber);
  delay(100000);//wait 100 seconds
}
