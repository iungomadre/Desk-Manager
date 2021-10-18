// setup.hpp

#if !defined(_SETUP_H)
#define _SETUP_H

#include <string>

#define CONNECTION_TIMEOUT 30     // maksymalna ilość prób połączenia z siecią WiFi
#define CONNECTION_TIMEOUT_ERROR    -1


int connectWiFi(char* wifi_ssid, char* wifi_password, ESP8266WiFiClass& wifi_module);
// connects to wifi network. throws exception when unavailable

#endif // _SETUP_H
