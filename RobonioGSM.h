#ifndef RobonioGSM_h
#define RobonioGSM_h
#include <SoftwareSerial.h>
#include "Arduino.h"

#define RX_PIN 10
#define TX_PIN 11	

class RobonioGSM{									
  private:
	int _timeout;
	String _tampon;
		String _serialOku();
  	
  public:

 	void start();	
	void reset();
	void soundOpen();
 	// arama metodları
 	bool callAnswer(); 	
 	void numberCall(char* number);
 	bool searchFinish();
 	uint8_t GetSearchStatus();   
 	//sms metodları
	bool smsSend(char* number,char* text);	 
	String smsRead(uint8_t index); 
	String NumberSmsRead(uint8_t index);
	bool allSmsDelete();    

	void signalQuality();
	void phoneSetFeature();
	void CarrierOpenProfile();
	void CarrierCloseProfile();
	//void RTCzaman(int *day,int *month, int *year,int *hour,int *minute, int *second);  
	String RTCtime();  
	String date(); 
	bool RTCupdate(int utc);  
};

#endif 
