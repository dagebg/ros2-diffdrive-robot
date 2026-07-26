#include <Arduino.h>
#include <Wire.h>
#include <WiFi.h>

#include "SECRETS.h"

const char* ap_ssid = ESP_WIFI_SSID;
const char* ap_password = ESP_WIFI_PASSWORD;

WiFiServer telnetServer(23);
WiFiClient telnetClient;

void debugPrint(const String &msg) {
  Serial.print(msg);
  if (telnetClient && telnetClient.connected()) {
    telnetClient.print(msg);
  }
}

void debugPrintln(const String &msg) {
  debugPrint(msg + "\n");
}

void scanI2C() {
  for (byte addr = 1; addr < 127; addr++) {
    Wire.beginTransmission(addr);
    byte error = Wire.endTransmission();
    if (error == 0) {
      String line = "I2C device found at address 0x";
      if (addr < 16) line += "0";
      line += String(addr, HEX);
      debugPrintln(line);
    } else if (error == 4) {
      String line = "Unknown error at address 0x";
      if (addr < 16) line += "0";
      line += String(addr, HEX);
      debugPrintln(line);
    }
  }
}

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);

  WiFi.softAP(ap_ssid, ap_password);
  IPAddress apIP = WiFi.softAPIP();

  Serial.println("=== ESP32 SoftAP started ===");
  Serial.print("SSID: ");
  Serial.println(ap_ssid);
  Serial.print("Password: ");
  Serial.println(ap_password);
  Serial.print("IP address: ");
  Serial.println(apIP);
  Serial.println("Connect your laptop WiFi to this network, then:");
  Serial.println("telnet 192.168.4.1 23");

  telnetServer.begin();
  telnetServer.setNoDelay(true);

  delay(500);
  debugPrintln("I2C Scanner (WiFi AP debug ready)");
  debugPrintln("Scanning I2C bus...");
  scanI2C();
}

void loop() {
  if (telnetServer.hasClient()) {
    if (!telnetClient || !telnetClient.connected()) {
      if (telnetClient) telnetClient.stop();
      telnetClient = telnetServer.available();
      debugPrintln("Telnet client connected.");
    } else {
      telnetServer.available().stop();
    }
  }

  scanI2C();
  delay(5000);
}
