   /*
  (TR) kodu yükledikten sonra gps modülünü bağlamak gerekiyor
  (ENG) After uploading the code you need to connect the gps module

 */

#include <RobonioGSM.h>
RobonioGSM Robonio;
String smsText, smsNumber;
#define PhoneNumber  "+90**********" //  Write down the number of the phone that will communicate with the GSM shield, putting the country code in front of it.
#define LED_pin 13


#define GPS Serial
#include <TinyGPS.h>
TinyGPS gps;

double latu;
double lon;
String loc;
char loc2[255];

void setup() {
   /*
  digitalWrite(7, HIGH);
  delay(3000);
  digitalWrite(7, LOW);
 */
 // Delete the " /* and */ " above to automatically start the GSM shield
  Robonio.start();
  delay(2000);
  pinMode(LED_pin, OUTPUT);
  GPS.begin(9600);
  delay(2000);
  Robonio.allSmsDelete  ();
  delay(2000);
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
        digitalWrite(LED_pin, HIGH);
        Robonio.smsSend(PhoneNumber, "LED OPENED");
      }
      else if (smsText.indexOf("LEDCLOSE") != -1) {
        digitalWrite(LED_pin, LOW);
        Robonio.smsSend(PhoneNumber, "LED CLOSED");
      }
      else if (smsText.indexOf("WHERE") != -1 || smsText.indexOf("WHERE?") != -1 || smsText.indexOf("LOCATION") != -1) {
        delay(1000);

        bool newData = false;
        for (unsigned long start = millis(); millis() - start < 1000;) {
          while (GPS.available()) {
            char c = GPS.read();
            if (gps.encode(c))
              newData = true;
          }
        }

        if (newData) {
          float flat, flon;
          unsigned long age;
          gps.f_get_position(&flat, &flon, &age);
          latu = flat;
          lon = flon;
          loc = "www.google.com.tr/maps/place/" + String(latu, 6) + "," + String(lon, 6);
          loc.toCharArray(loc2, 100);
          delay(1000);
        }
        delay(1000);
        char loc2[255];
        loc.toCharArray(loc2, 100);
        Robonio.smsSend(PhoneNumber, loc2);
      }
      else {
      }
      Robonio.allSmsDelete();
    }
  }
}
