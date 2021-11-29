// main.cpp

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
#include "../include/animations.hpp"
#include "../include/components.hpp"
#include "../include/setup.hpp"
#include "../include/htmlServer.hpp"

// konfiguracja sieci
#define SSID        "nazwa"
#define PASSWORD    "haslong"

// konfiguracja świecidełek
// #define _PIXELS
 #define _RGB
// #define _MONO

//ŁUKASZOWE ZMIENNE

const int sampleWindow = 10; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;
int signalMax, signalMin, peakToPeak;
unsigned long startMillis;

//ŁUKASZOWA FUNKCJA

void micro()
{
  signalMin = 1024;
  signalMax = 0;
  startMillis = millis();
  while((millis() - startMillis < sampleWindow))
  {
    sample = analogRead(A0);
      if (sample < 1024)  // toss out spurious readings
      {
         if (sample > signalMax)
         {
            signalMax = sample;  // save just the max levels
         }
          else if (sample < signalMin)
         {
            signalMin = sample;  // save just the min levels
         }
      }
    peakToPeak = signalMax - signalMin;
    Serial.println(peakToPeak);
    setRGBcolor(peakToPeak, 0, 0, 1);
  }
}

//KONIEC

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
  pinMode(A0,INPUT); //MIKROFON
  
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
    Serial.println(WiFi.localIP());
    
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

  //ŁUKASZOWY TIMER
  startMillis= millis();
}


void loop() 
{
// poniższy kod będzie uruchamiany w pętli

  //MIKROFON
  micro();

  // sprawdzenie, czy został wciśnięty fizyczny przycisk na płytce
  checkButtonPressed(lamp, myTime);

  // nawiązywanie połączenia z klientem
  int clientStatus = getAvailableClient(client, server);
  if(clientStatus == CLIENT_NOT_AVAILABLE_ERROR)
      return;
  

  // wyświetlenie strony
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
  if(playAnimation[RGB_ANIMATION_1]) animateRGB(RGB_ANIMATION_1);
  #endif

  #ifdef _MONO
  setMONObrightness(brightness);
  if(playAnimation[MONO_ANIMATION_1]) animateMONO(MONO_ANIMATION_1);
  #endif
}
