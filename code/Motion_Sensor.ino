/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-motion-sensor
 */

//-----------------------------------------------------------------------------------
// wifi settings: 
#include <WiFi.h>
#include <Arduino.h>   // Include the Arduino library
#include <Wire.h>      // Include the Wire library for I2C communication
#include "ThingSpeak.h"

// Set the ThingSpeak channel and API key information
unsigned long myChannelNumber = 2076230;
const char* myWriteAPIKey = "DDKT7ELV5UW18KYD";

// Set the WiFi network credentials
const char* ssid = "HUJI-guest"; // your wifi SSID name
const char* password = ""; // wifi password
//const char* ssid = "Raniphone"; // your wifi SSID name
//const char* password = "12345670"; // wifi password


// Set the ThingSpeak server address
const char* server = "api.thingspeak.com";

// Create a WiFiClient object to connect to the WiFi network
WiFiClient client;

// Set the time to wait between uploading data to ThingSpeak (in milliseconds)
int wait_between_uploads = 5000; // 5 seconds



//-------------------------------------------------------------------------------------

const int PIN_TO_SENSOR = A4; // A4 pin connected to OUTPUT pin of sensor
int pinStateCurrent   = LOW;  // current state of pin
int pinStatePrevious  = LOW;  // previous state of pin

void setup() {
  Serial.begin(115200);            // initialize serial
    // Disconnect any previous WiFi connection
  WiFi.disconnect();
  delay(10);

  // Connect to the WiFi network
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("ESP32 connected to WiFi: ");
  Serial.println(ssid);
  Serial.println();

  // Initialize the ThingSpeak library with the WiFi client
  ThingSpeak.begin(client);

  pinMode(PIN_TO_SENSOR, INPUT); // set ESP32 pin to input mode to read value from OUTPUT pin of sensor
}

void loop() {
  float is_motion = 0;
  pinStatePrevious = pinStateCurrent; // store old state
  pinStateCurrent = digitalRead(PIN_TO_SENSOR);   // read new state



  if (pinStatePrevious == LOW && pinStateCurrent == HIGH) {   // pin state change: LOW -> HIGH
    Serial.println("Motion detected!");
    is_motion = 1;
    ThingSpeak.setField(5, is_motion);
    ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
    delay(10000);

  }

  is_motion = 0;
  ThingSpeak.setField(5, is_motion);
  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  is_motion = 0;


  // Print a message to the serial monitor indicating that the data has been uploaded
  Serial.println("Uploaded to ThingSpeak server.");

  // Disconnect the WiFi client
  client.stop();

  // Wait for the specified amount of time before uploading the next set of data
  // thingspeak needs minimum 15 sec delay between updates on a free acount,
  // a paid acount can update every 1 sec
  Serial.println("Waiting to upload next reading...");
  Serial.println();
  delay(1000);

}