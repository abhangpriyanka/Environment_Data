#include <WiFi.h>
#include <HTTPClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 14
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

const char* ssid = "Wokwi-GUEST";
const char* password = "";


const char* supabaseUrl = "https://zzszxmzmumhbsqimjqal.supabase.co/rest/v1/environment_Data";
const char* supabaseKey = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJzdXBhYmFzZSIsInJlZiI6Inp6c3p4bXptdW1oYnNxaW1qcWFsIiwicm9sZSI6ImFub24iLCJpYXQiOjE3NjI5MzAzMzgsImV4cCI6MjA3ODUwNjMzOH0.fEX9FTNWWWIj4rmnV2usDnlSyeVZBaFDSEEpof5Sokk"; // <-- use your actual anon key

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { 
    delay(500); 
    Serial.print("."); 
  }
  Serial.println("WiFi connected");
  sensors.begin();
}

void loop() {
  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);
  String status = (tempC > 30.0) ? "High" : "Normal";

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(supabaseUrl);
    http.addHeader("Content-Type", "application/json");
    http.addHeader("apikey", supabaseKey);

    // ✅ FIXED LINE: use String() to concatenate
    String authHeader = "Bearer " + String(supabaseKey);
    http.addHeader("Authorization", authHeader);

    String payload = "{\"temperature\":" + String(tempC, 2) + ",\"stetus\":\"" + status + "\"}";
    int httpResponseCode = http.POST(payload);

    Serial.print("Temp: "); Serial.print(tempC);
    Serial.print(" °C | Status: "); Serial.print(status);
    Serial.print(" | Response: "); Serial.println(httpResponseCode);

    http.end();
  }
  delay(10000);
}
