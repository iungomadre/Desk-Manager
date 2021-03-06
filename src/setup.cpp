// setup.cpp

#include <ESP8266WiFi.h>
#include "../include/setup.hpp"


int connectWiFi(char* wifi_ssid, char* wifi_password, ESP8266WiFiClass& wifi_module)
{
  wifi_module.begin(wifi_ssid, wifi_password);
  for (int i = 0; i != CONNECTION_TIMEOUT; i++)
  {
    if(wifi_module.status() == WL_CONNECTED)
      return 0;
    delay(500);
  }
  return CONNECTION_TIMEOUT_ERROR;
}

void promptNotConnected()
{
  Serial.println("Cannot connect to WiFi - connection timeout.");
  Serial.println("Reset board to retry or check your WiFi settings\n...\n");
}

void promptConnected()
{
  Serial.println("Succesfully connected to WiFi. Starting program");
}

void halt()
{
  while(true)
    delay(10000);
}
