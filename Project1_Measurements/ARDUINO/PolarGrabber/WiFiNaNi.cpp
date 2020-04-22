#include "WiFiNaNi.h"

/*
 * Disconnects WiFi and turns of WiFi module
 */
void WiFiNaNi::dissable_connection_to_wifi()
{
  Serial.println("METHOD: dissable connection to wifi");
  //delay(10000);
  WiFi.disconnect();
  WiFi.end();
  Serial.println("LOG: wifi ended");
  Serial.print("wifi status after disconnect = ");
  Serial.println(WiFi.status());
  Serial.println("LOG: wifi status updated");
}

 // check if the WiFi module works
bool WiFiNaNi::check_wifi_shield()
{
  if (WiFi.status() == WL_NO_SHIELD) 
  {
    Serial.println("NO WIFISHIELD PRESENT");
    // don't continue:
    return false;
  }
  return true;
}

/*  
 *   Makes a connection to the WiFi network and prints it status.
 */
bool WiFiNaNi::make_connection_to_wifi(char ssid[], char pass[])
{  
  if( ! check_wifi_shield()) return false;
    
  WiFi.begin(ssid, pass);
  // wait 10 seconds for connection:
  delay(10000);
  Serial.print("wifi status = ");
  Serial.println(WiFi.status());
  
  if(WiFi.status() == WL_CONNECTED) return true;

  if(WiFi.status() != WL_CONNECTED) Serial.println("FAILED TO CONNECT TO WIFI");
  return false;
}

/*
 * Send one measurement to server.
 */ 
bool WiFiNaNi::http_request(IPAddress ip, int port, WiFiClient client, unsigned char SO2, unsigned char NO2, unsigned char PM10, unsigned char PM25, unsigned char O3, unsigned long timestamp, unsigned char id)
{
  Serial.println("METHOD: http request");

  // example url
  //http://localhost/add.php?Sensor_SO2=3&Sensor_CO=5&Sensor_PM10=10&Sensor_PM25=2.5&Sensor_O3=33&Sensor_locatie=hier&Sensor_timestamp=12589613

  if (client.connect(ip, port)) {
    Serial.println("Connected!");
    client.print("GET /add.php?");
    client.print("Sensor_SO2=");
    client.print(SO2);
    client.print("&Sensor_CO=");
    client.print(NO2);
    client.print("&Sensor_PM10=");
    client.print(PM10);
    client.print("&Sensor_PM25=");
    client.print(PM25);
    client.print("&Sensor_O3=");
    client.print(O3);
    client.print("&Sensor_locatie=");
    client.print(id);
    client.print("&Sensor_timestamp=");
    client.print(timestamp);
    client.println(" HTTP/1.1");
    client.print("Host: "); 
    client.println(ip); 
    client.println("Connection: close"); 
    client.println(); 
    client.println(); 
    client.stop();

    return true;
  }
  else {
    Serial.println("connection failed");
    return false;
  }
  
}
