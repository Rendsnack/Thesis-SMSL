#ifndef WFL
#define WFL

#if (ARDUINO >= 100)
	#include "Arduino.h"
	#include "WiFiNINA.h"
#else
	#include "WProgram.h"
	#include "WiFiNINA.h"
#endif


class WiFiNaNi
{
  public:
  //concstructor

  //method
  static void dissable_connection_to_wifi();

  static bool make_connection_to_wifi(char ssid[], char pass[]);

  static bool http_request(IPAddress ip, int port, WiFiClient client, unsigned char SO2, unsigned char NO2, unsigned char PM10, unsigned char PM25, unsigned char O3, unsigned long timestamp, unsigned char id);
  
  private: 
  static bool check_wifi_shield();
};



#endif
