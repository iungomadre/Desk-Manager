// main.cpp

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

// konfiguracja świecidełek
#define _PIXELS
// #define _RGB
// #define _MONO

// zmienne do obsługi strony HTML 
WiFiServer server(80);
WiFiClient client;
String request;

// zmienne dla świecidełek
Adafruit_NeoPixel pixels(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);
float brightness = 1;
int red = 0, green = 0, blue = 0;
bool playAnimation[NUM_ANIMATIONS];

// pozostałe
Relay lamp(LAMP_OUT, ON);
unsigned long myTime = 0;


void setup()
// poniższy kod uruchomi się tylko raz
{
  pinMode(LAMP_OUT, OUTPUT);
  pinMode(LAMP_SWITCH, INPUT_PULLUP);
  pinMode(RED_OUT, OUTPUT);
  pinMode(GREEN_OUT, OUTPUT);
  pinMode(BLUE_OUT, OUTPUT);
  pinMode(LED_MONO_OUT, OUTPUT);
  
  Serial.begin(9600);
  pixels.begin();
  server.begin();

  // połącz z WiFi
  if(connectWiFi(SSID, PASSWORD, WiFi) == CONNECTION_TIMEOUT_ERROR)
  {
    promptNotConnected();
    halt();
  } else
  {
    promptConnected();
    
    // włącz wejściowe animacje
    #ifdef _PIXELS
    delay(1);
    animatePixels(PIXELS_ENTRY_ANIMATION, brightness, pixels);
    #endif // _PIXELS

    #ifdef _RGB
    delay(1);
    // animateRGB(RGB_ENTRY_ANIMATION);  <- TODO
    #endif

    #ifdef _MONO
    delay(1);
    // animateMONO(MONO_ENTRY_ANIMATION); <- TODO
    #endif
  }

  // ustaw animacje jako domyślnie wyłączone
  for(int i = 0; i < NUM_ANIMATIONS; i++) playAnimation[i] = false;
}


void loop() {
// poniższy kod będzie uruchamiany w pętli

  // sprawdzenie, czy został wciśnięty fizyczny przycisk na płytce
  checkButtonPressed(lamp, myTime);

  // sprawdzenie, czy dostępny klient
  client = server.available();
  if (client.available())
  {
    // wyświetlanie strony
    printHTML(client);

    // modyfikacja zmiennych na podstawie requesta
    request = client.readStringUntil('\r');
    decodeRequestedColors(request, red, green, blue);
    decodeRequestedAnimations(request, playAnimation);
    decodeRequestedBrightness(request, brightness);
    decodeRequestedLampSwitch(request, lamp);

    // wykonanie poleceń na podstawie zmiennych
    #ifdef _PIXELS
    setPixelsColor(red, green, blue, brightness, pixels);
    if(playAnimation[PIXELS_ANIMATION_1]) animatePixels(PIXELS_ANIMATION_1, brightness, pixels);
    if(playAnimation[PIXELS_ANIMATION_2]) animatePixels(PIXELS_ANIMATION_2, brightness, pixels);
    #endif // _PIXELS

    #ifdef _RGB
    setRGBcolor(red, green, blue, brightness);
    if(playAnimation[RGB_ANIMATION_1]) animate(RGB_ANIMATION_1, brightness, pixels);
    #endif

    #ifdef _MONO
    setMonoLEDbrightness(brightness);
    if(playAnimation[MONO_ANIMATION_1]) animate(MONO_ANIMATION_1, brightness, pixels);
    #endif
  }
}
