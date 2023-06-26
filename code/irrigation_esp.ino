#include <WiFi.h>

// Include the ThingSpeak library
#include "ThingSpeak.h"

#include "Adafruit_SHT31.h" // Include the SHT31 library from Adafruit

// Set the ThingSpeak channel and API key information
unsigned long myChannelNumber = 2076230;
const char* myWriteAPIKey = "DDKT7ELV5UW18KYD";

// Set the WiFi network credentials
const char* ssid = "TP-Link_905D"; // your wifi SSID name
const char* password = "33072036"; // wifi password

// Set the ThingSpeak server address
const char* server = "api.thingspeak.com";

// Create a WiFiClient object to connect to the WiFi network
WiFiClient client;

// Set the time to wait between uploading data to ThingSpeak (in milliseconds)
int wait_between_uploads = 10000; // 10 seconds

Adafruit_SHT31 sht31 = Adafruit_SHT31(); // Create an instance of the SHT31 object

const int analog_pin1 = A0; // Pin into which we connect the input voltage
const int analog_pin2 = A1; // Pin into which we connect the input voltage
const int analog_pin3 = A2; // Pin into which we connect the input voltage
const int analog_pin4 = A3; // Pin into which we connect the input voltage
float val1 = 0 ; 
float val2 = 0 ;
float val3 = 0 ;
float val4 = 0 ;// variable to store the value read
float Volt1 = 0;
float Volt2 = 0;
float Volt3 = 0;
float Volt4 = 0;
float Moisture1 = 0;
float Moisture2 = 0;
float Moisture3 = 0;
float Moisture4 = 0;
int relaypin1 = D5;
int relaypin2 = D6;
int relaypin3 = D7;
int relaypin4= D3;
void setup() {
  Serial.begin(115200);
  pinMode(relaypin1, OUTPUT);
  pinMode(relaypin2, OUTPUT);
  pinMode(relaypin3, OUTPUT);
  pinMode(relaypin4, OUTPUT);
    if (! sht31.begin(0x44)) {  // Check if SHT31 is connected and start it with address 0x44
    Serial.println("Couldn't find SHT31"); // Print an error message if SHT31 is not found
    while (1) delay(1);  // Wait indefinitely
  }
//   Disconnect any previous WiFi connection
  WiFi.disconnect();
  
  delay(10);

//   Connect to the WiFi network
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
}

float val_to_volt(float val) {
  float volt = val*(3.3/4096);
  return volt;
}

float volt_to_moisture(float Volt) {
  float moisture = (-62.5*Volt)+150;
  return moisture;
}

void loop() {
 
  float t = sht31.readTemperature(); // Read temperature from SHT31 and store it in t variable
  float h = sht31.readHumidity();    // Read humidity from SHT31 and store it in h variable
  float es = exp(((16.78*t) - 116.9)/ (t+237.3));
  float ed = es * (h/100);
  float vpd = es - ed;
  Serial.print("Current temperature: ");
  Serial.println(t);
  Serial.print("Current VPD: ");
  Serial.println(vpd);
  val1 = analogRead(analog_pin1);  // read the input pin
  val2 = analogRead(analog_pin2);
  val3 = analogRead(analog_pin3);
  val4 = analogRead(analog_pin4);
  
  Volt1 = val_to_volt(val1);
  Moisture1 = volt_to_moisture(Volt1);
  Serial.print("Voltage1: ");
  Serial.println(Volt1);
  Serial.print("Moisture1: ");
  Serial.println(Moisture1);
  
  Volt2 = val_to_volt(val2);
  Moisture2 = volt_to_moisture(Volt2);
  Serial.print("Voltage2: ");
  Serial.println(Volt2);
  Serial.print("Moisture2: ");
  Serial.println(Moisture2);
  
  Volt3 = val_to_volt(val3);
  Moisture3 = volt_to_moisture(Volt3);
  Serial.print("Voltage3: ");
  Serial.println(Volt3);
  Serial.print("Moisture3: ");
  Serial.println(Moisture3);

  Volt4 = val_to_volt(val4);
  Moisture4 = volt_to_moisture(Volt4);
  Serial.print("Voltage4: ");
  Serial.println(Volt4);
  Serial.print("Moisture4: ");
  Serial.println(Moisture4);

//  Set the values to be sent to ThingSpeak
  ThingSpeak.setField(1, Moisture1);
  ThingSpeak.setField(2, Moisture2);
  ThingSpeak.setField(3, Moisture3);
  ThingSpeak.setField(4, Moisture4);
  ThingSpeak.setField(6, t);
  ThingSpeak.setField(7, vpd);
// Send the data to ThingSpeak
  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

  // Print a message to the serial monitor indicating that the data has been uploaded
  Serial.println("Uploaded to ThingSpeak server.");

  // Disconnect the WiFi client
  client.stop();

  // Wait for the specified amount of time before uploading the next set of data
  // thingspeak needs minimum 15 sec delay between updates on a free acount,
  // a paid acount can update every 1 sec
  Serial.println("Waiting to upload next reading...");
  Serial.println();
  Serial.println();
  
  delay(wait_between_uploads);
  
  if (Moisture1<40){
    digitalWrite(relaypin1, HIGH);
  }
  if(Moisture1>=60){
    digitalWrite(relaypin1, LOW);
  }
  
  if (Moisture2<40){
    digitalWrite(relaypin2, HIGH);
  }
  if(Moisture2>=60){
    digitalWrite(relaypin2, LOW);
  }
  
  if (Moisture3<40){
    digitalWrite(relaypin3, HIGH);
  }
  if(Moisture3>=60){
    digitalWrite(relaypin3, LOW);
  }
  
  if (Moisture4<40){
    digitalWrite(relaypin4, HIGH);
  }
  if(Moisture4>=60){
    digitalWrite(relaypin4, LOW);
  }
}
