#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

#define CRASH_THRESHOLD 18 // adjust this value to set the crash detection threshold

SoftwareSerial gpsSerial(16, 17); // RX, TX pins for GPS module
TinyGPSPlus gps; // create a TinyGPS++ object

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345); // create an ADXL345 object

void setup() {
  Serial.begin(9600);
  while (!Serial); // wait for serial port to connect
  gpsSerial.begin(9600); // start the software serial for the GPS module
  accel.begin(); // start the accelerometer
}

void loop() {
  sensors_event_t event; 
  accel.getEvent(&event); // read accelerometer data
  float accel_magnitude = sqrt(event.acceleration.x * event.acceleration.x + event.acceleration.y * event.acceleration.y + event.acceleration.z * event.acceleration.z); // calculate the magnitude of the acceleration vector
  if (accel_magnitude >= CRASH_THRESHOLD) { // check if a crash has been detected
    while (gpsSerial.available() > 0) {
      if (gps.encode(gpsSerial.read())) { // read GPS data
        if (gps.location.isValid()) { // check if GPS data is valid
          Serial.print("Crash detected! GPS coordinates: ");
          Serial.print(gps.location.lat(), 6);
          Serial.print(", ");
          Serial.println(gps.location.lng(), 6);
          delay(1000); // wait for 1 second before printing again (to avoid repeated printing)
        }
      }
    }
  }
}