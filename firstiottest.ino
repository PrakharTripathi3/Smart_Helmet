#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <base64.h>

const char* ssid     = "Infinix ZERO 5G";
const char* password = "87654321";
const char* account_sid = "ACb3030250e20b7fc0449faecb76056549";
const char* auth_token = "b16bad3042efbe70e812f31c2b251da9";
const char* twilio_phone_number = "+15076876964";
const char* recipient_phone_number = "+919654937307";

#define CRASH_THRESHOLD 18 

SoftwareSerial gpsSerial(16, 17); 
TinyGPSPlus gps; 

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345); 


void sendSMS(String message) {
  HTTPClient http;
  http.begin("https://api.twilio.com/2010-04-01/Accounts/" + String(account_sid) + "/Messages.json");
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  http.setAuthorization(account_sid, auth_token);
  String postData = "From=" + String(twilio_phone_number) + "&To=" + String(recipient_phone_number) + "&Body=" + message;
  int httpResponseCode = http.POST(postData);
  http.end();
}

void setup() {
  Serial.begin(9600);
  while (!Serial); 
  gpsSerial.begin(9600); 
  accel.begin(); 
 Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println(" connected");
}

void loop() {
  sensors_event_t event; 
  accel.getEvent(&event); 
  float accel_magnitude = sqrt(event.acceleration.x * event.acceleration.x + event.acceleration.y * event.acceleration.y + event.acceleration.z * event.acceleration.z); // calculate the magnitude of the acceleration vector
  if (accel_magnitude >= CRASH_THRESHOLD) { 
    while (gpsSerial.available() > 0) {
      if (gps.encode(gpsSerial.read())) { 
        if (gps.location.isValid()) { 
          String message = "Crash detected! GPS coordinates: " + String(gps.location.lat(), 6) + ", " + String(gps.location.lng(), 6);
          sendSMS(message);
          Serial.println(message);
          delay(1000);
        }
      }
    }
  }
}






























if (gps.location.isValid()) {
  int numSatellites = gps.satellites.value();
  Serial.print("Number of satellites: ");
  Serial.println(numSatellites);
}
