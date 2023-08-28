#include <SoftwareSerial.h>
#include <TinyGPS++.h>

SoftwareSerial gpsSerial(16,17); // RX, TX
TinyGPSPlus gps;

void setup() {
  Serial.begin(9600);
  while (!Serial) {}

  gpsSerial.begin(9600);
  gpsSerial.print("hello");
  
}

void loop() {
  while (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) {
      if (gps.location.isValid()) {
        Serial.print("Latitude: ");
        Serial.print(gps.location.lat(), 6);
        Serial.print(", Longitude: ");
        Serial.println(gps.location.lng(), 6);
        delay(2000);
      }
    }
  }
}