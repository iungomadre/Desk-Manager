// main.cpp

// importowanie bibliotek
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
#include "../include/animations.hpp"
#include "../include/components.hpp"
#include "../include/setup.hpp"
#include "../include/htmlServer.hpp"

// konfiguracja sieci
#define SSID        "home san oke dyk pastafarialand"
#define PASSWORD    "niechBedzieWielbionaJegoKluskowatosc"


// zmienne do obsługi strony HTML 
WiFiServer server(80);
WiFiClient client;

// zmienne paska LED
Adafruit_NeoPixel pixels(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);
float brightness=1;
int red, green, blue = 0;
bool playAnimation[2] = {false, false};
float animationSpeed[2] = {0.5, 1};

// pozostałe
Relay lamp(LAMP_OUT, ON); // nie wiem, czy ta klasa w ogóle jest potrzebna - TODO
unsigned long myTime = 0;


void setup()
{
  pinMode(LAMP_OUT, OUTPUT);
  pinMode(LAMP_SWITCH, INPUT_PULLUP);
  pinMode(RED_OUT, OUTPUT);
  pinMode(GREEN_OUT, OUTPUT);
  pinMode(BLUE_OUT, OUTPUT);
  pinMode(LED_MONO_OUT, OUTPUT);
  
  Serial.begin(9600);
  pixels.begin();

  if(connectWiFi(SSID, PASSWORD, WiFi) == CONNECTION_TIMEOUT_ERROR)
  {
    promptNotConnected();
    halt();
  } else
  {
    promptConnected();
    animate(ENTRY_ANIMATION, brightness, pixels);
  }

  server.begin();
}


void loop() {
// poniższy kod będzie uruchamiany w pętli
  
  // obsługa strony HTML (sterowanie)
  int clientStatus = getAvailableClient(server, client);
  if(clientStatus == CLIENT_NOT_AVAILABLE_ERROR)
  {
    //... TODO
  }
  else if(clientStatus == CLIENT_UNREACHABLE_ERROR)
  {
    //... TODO
  }

  String request = client.readStringUntil('\r');
  decodeRequestedColors(request, red, green, blue);
  decodeRequestedAnimations(request, playAnimation);
  decodeRequestedBrightness(request, brightness);
  decodeRequestedLampSwitch(request, lamp);

  // wykonanie poleceń na podstawie request'a
  if(playAnimation[0]) animate(ANIMATION_1, brightness, pixels);
  if(playAnimation[1]) animate(ANIMATION_2, brightness, pixels);
  setColor(red, green, blue, brightness, pixels);
  
  // sprawdzenie, czy został wciśnięty fizyczny przycisk na płytce
  checkButtonPressed(lamp, myTime);

  delay(1);
}
