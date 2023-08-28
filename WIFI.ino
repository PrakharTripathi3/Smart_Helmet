#include <WiFi.h>

const char* ssid = "Pranshu c-802";
const char* password = "Pranshu@2020";

void setup() {
  Serial.begin(9600);  
  delay(1000);

  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // your code here
}