
#include <SPI.h>
#include <WiFiNINA.h>

#include "Rotator.h"
#include "WiFiNaNi.h"
#include "Packet.h"

// #define ENABLE_ROTATOR
#define ENABLE_WIFI
//#define ENABLE_SERIAL_COMMANDS
//#define REPLY_IN_DEGREES

char ssid[] = "thesis";
char pass[] = "12345678";

IPAddress server(10, 46, 217, 181);
int port = 4242;

WiFiClient client;

bool sendRequest = true;

struct command
{
  int key;
  int data;  
};

int pos = 0;

/*
 * Blink the onboard LED twice
 */
void blink_onboard_LED(int amount)
{
  for (int i = 0; i < amount; i++)
  {
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
  }
  digitalWrite(LED_BUILTIN, LOW);
}

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200); //Serial Monitor

  Rotator::init();

  #ifdef ENABLE_WIFI
  //connect to wifi
  bool connection_made = false;
  while ( WiFiNaNi::make_connection_to_wifi(ssid, pass) == false )
  {
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("No connection made.");
    delay(1000);
    digitalWrite(LED_BUILTIN, HIGH);
  }
  Serial.println("connected to wifi");
  blink_onboard_LED(2);

  //connect to server
  Serial.println();
  digitalWrite(LED_BUILTIN, HIGH);
  while( client.connect(server, port) != 1 )
  {
    Serial.println("Can't connect to server.");
    blink_onboard_LED(4);
    digitalWrite(LED_BUILTIN, HIGH);
  }
  Serial.println("connected to server");
  blink_onboard_LED(2);

//  sendToServer('1');

  //send confirmation to server
//  String hello = "arduino connected";
//  client.print(0);
//  client.print("\n"); //vs println()
//  client.write(sizeof(hello));
//  client.print("\n");
//  client.print("hello");
//  client.print("\n");
  #endif

  #ifdef ENABLE_ROTATOR
  Rotator::setStepSizeInSteps(5);
  #endif
}

void loop()
{
  #ifdef ENABLE_ROTATOR
    Rotator::takeOneStepCLKWise();
    Rotator::takeOneStepCLKWise();
    Rotator::takeOneStepCLKWise();
    Rotator::takeOneStepCLKWise();
    Rotator::takeOneStepCLKWise();
    Serial.print("pos: "); Serial.println(Rotator::getPositionInSteps());
    delay(2000);
  #endif

  #ifdef ENABLE_WIFI
    blink_onboard_LED(2);
    command received_command_client;
    listenToServer(&received_command_client);
    if( received_command_client.key != -1 )
    {
      Serial.print("received_command.key = "); Serial.println(received_command_client.key);
      Serial.print("received_command.data = "); Serial.println(received_command_client.data);
      //execute command
      interpretCommand(&received_command_client);
    }
  #endif

  #ifdef ENABLE_SERIAL_COMMANDS
    command received_command;
    listenToSerialPrompt(&received_command);
    if( received_command.key != -1 )
    {
      Serial.print("received_command.key = "); Serial.println(received_command.key);
      Serial.print("received_command.data = "); Serial.println(received_command.data);
      //execute command
      interpretCommand(&received_command);
    }
    delay(50);
  #endif
}

void sendToServer(char command)
{
  #ifdef ENABLE_WIFI
  Serial.print("sending to server: "); Serial.println(command);
  delay(1000);
//  if( client.connect(server, port) == false )
//  {
//    Serial.println("Failed to connect to server.");
//    return;
//  }  
  int bytesSend = client.print(command);
  Serial.print("bytes send to server: "); Serial.println(bytesSend);
  #endif
}


/*
 * Listen for a command being inputted in the Serial prompt and store it 'received_command'.
 * A command consist of a key and possibly some data. Both need to be an int between 1 and 9.
 * At the time of this writing all keys higher than 6 are expected to have some corresponding data.
 */
void listenToSerialPrompt(command * received_command)
{
  received_command->key = -1;
  received_command->data = -1;

  received_command->key = extractIntFromSerial();

  if( received_command->key < 5) //need to extract data acompaning key
  {
    received_command->data = extractIntFromSerial();
  }
}

int listenToServer(command * received_command)
{
  received_command->key = -1;
  received_command->data = -1;
  
  received_command->key = extractIntFromClient();

  if( received_command->key < 5) //need to extract data acompaning key
  {
    received_command->data = extractIntFromClient();
  }
}

int extractIntFromClient()
{
  int result = -1;
  unsigned long startTime = millis();
  bool received = false;
  while ( !received ) 
  {
    if (client.available()) 
    {
      received = true;
      char c = client.read();
      Serial.println(); Serial.print("Incoming byte: "); Serial.println(c);
      if( isdigit(c) == 0 )
      {
        Serial.println("This is not a digit.");
        return result;
      }
      
      int data = atoi(&c);
      if( (data>= 0) && (data<10) ) //valid command
      {
        result = data;
      }
    }
  }
  return result;
}

int extractIntFromSerial()
{
  int result = -1;
  if(Serial.available()) 
  {
    char c = Serial.read();
    Serial.println(); Serial.print("Incoming byte: "); Serial.println(c);
    if( isdigit(c) == 0 )
    {
      Serial.println("This is not a digit.");
      return result;
    }
    
    int data = atoi(&c);
    if( (data>= 0) && (data<10) ) //valid command
    {
      result = data;
    }

    Serial.print("Incoming int: "); Serial.println(result);
  }
  return result;
}


void interpretCommand(command * command)
{
  switch (command->key)
  {
  case 9:
    Rotator::reset();
    break;

  case 0:
    Serial.println("calibrate");
    Rotator::calibrate();
    break;

  case 2:
    if( command->data == -1)
    {
      sendToServer('255');
      Serial.println("Invalid data");
      break;
    }
    Rotator::setPositionInSteps(command->data);
    sendToServer('1');
    break;

  case 7:
    Serial.print("current position in steps = "); Serial.println(Rotator::getPositionInSteps());
    sendToServer(Rotator::getPositionInSteps());
    break;
  
  case 1:
    if( command->data == -1)
    {
      sendToServer('255');
      Serial.println("Invalid data");
      break;
    }
    Rotator::setStepSizeInSteps(command->data);
    sendToServer('1');
    break;

  case 8:
    Serial.print("current step size in steps = "); Serial.println(Rotator::getStepSizeSteps());
    sendToServer(Rotator::getStepSizeSteps());
    break;

  case 5:
    Rotator::takeOneStepCLKWise();
    sendToServer('1');
    break;

  case 6:
    Rotator::takeOneStepCounterCLKWise();
    sendToServer('1');
    break;

  default:
    sendToServer('255');
    Serial.println("DEFAULT CASE");
    break;
  }
}
