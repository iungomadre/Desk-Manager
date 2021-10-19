// main.cpp

// importowanie bibliotek
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
#include "../include/animations.hpp"
#include "../include/components.hpp"
#include "../include/setup.hpp"

// konfiguracja sieci
#define SSID        "home san oke dyk pastafarialand"
#define PASSWORD    "niechBedzieWielbionaJegoKluskowatosc"


// zmienne
Adafruit_NeoPixel pixels(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);
WiFiServer server(80);
String colorHex = "";
String request;
Relay lamp(LAMP_OUT, ON);
WiFiClient client;

// parametry LED
int red, green, blue = 0;
float brightness=1;

// parametry animacji
bool playAnimation1=0;
bool playAnimation2=0;
float Anim1Speed=0.5;
float Anim2Speed=2;

// jakieś inne gówna
int number;
int timewate, Length;
unsigned long myTime = 0;

void setup()
{
  pinMode(LAMP_OUT, OUTPUT);
  pinMode(LAMP_SWITCH, INPUT_PULLUP);
  
  Serial.begin(9600);
  pixels.begin();

  if(connectWiFi(SSID, PASSWORD, WiFi) == CONNECTION_TIMEOUT_ERROR)
  {
    promptNotConnected();
    halt();
  }
  else
  {
    promptConnected();
    animate(ENTRY_ANIMATION, brightness, pixels);
  }

  server.begin();
}

void loop() {
// poniższy kod będzie uruchamiany w pętli
  
  // sprawdzenie, czy nie został wciśnięty fizyczny przycisk
  checkButtonPressed(lamp, myTime);

  // odświeżenie lampki
  digitalWrite(LAMP_OUT, lamp.getStatus());

  // włączenie animacji
  if(playAnimation1) animate(ANIMATION_1, brightness, pixels);
  if(playAnimation2) animate(ANIMATION_2, brightness, pixels);

  // wyświetlenie strony HTML - do całkowitego przerobienia
  client = server.available();
  if (!client) {
    return;
  }
  timewate = 0;
  while (!client.available()) {
    delay(1);
    if (++timewate > 1800)
    {
      //timeout
      client.stop();
      return;
    }
  }

  request = client.readStringUntil('\r');
  Length = request.length();
  int i = 0;

  if (request.charAt(5) != '%');
  else
  {
    red = 0;
    green = 0;
    blue = 0;
    colorHex="";

    while (i < Length)
    {
      if (request.charAt(i) == '%' && request.charAt(i + 1) == '2' && request.charAt(i + 2) == '3')
      {
        for (int m = i + 3; m < i + 9; m++) colorHex += request.charAt(m);
        break;
      }
      i++;
    }

    number = (int) strtoll(&colorHex[0], NULL, 16);

    Serial.print("#");
    Serial.println(colorHex);

    red = number >> 16;
    green = number >> 8 & 0xFF;
    blue = number & 0xFF;

    playAnimation1=false;
    playAnimation2=false;
    setColor(red, green, blue, brightness, pixels);
  }   
 
  client.flush();

  if (request.indexOf("/LEDOFF") != -1){setColor(0, 0, 0, 1, pixels); playAnimation1=false; playAnimation2=false;}
  if (request.indexOf("/LED50") != -1)   {brightness=0.5; setColor(red,green,blue,0.5, pixels);}
  if (request.indexOf("/LED100") != -1)  {brightness=1;  setColor(red,green,blue,1, pixels);}

  if (request.indexOf("/ANIM1") != -1)  {playAnimation1 = true; playAnimation2=false;}
  if (request.indexOf("/ANIM2") != -1)  {playAnimation1=false; playAnimation2=true;}

  if (request.indexOf("/LAMP") != -1)  lamp.toggle();

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<center>");
  client.println("<p><font size=\"7\">");

  client.println("<body bgcolor=\"#d6d6c2\">");
  client.print("<form action=\" / action_page.php\">");
  client.print("RGB: ");
  client.print("<br/> ");

  client.println("<table>");
  client.println("<tr>");
  client.println("<td>");

  client.print("<input style=\"height:80px;width:200px\" type=\"color\" name=\"color\" value=\"#42bcf4\">");
  client.print("<br/> ");
  client.print("<a><button style=\"height:40px;width:200px\" type=\"submit\">WYSLIJ</button></a>");
  client.print("<br/> ");
  client.println ("<a href=\"LEDOFF\"><button style=\"height:40px;width:200px\" type=\"button\">WYLACZ</button></a>");
  client.println("</form>");
  client.print("<br/> ");

  client.println("</td>");
  client.println("<td>");

  client.println ("<a href=\"LED50\"><button style=\"height:40px;width:150px\" type=\"button\">50% Brightness</button></a>");
  client.print("<br/> ");
  client.println ("<a href=\"LED100\"><button style=\"height:40px;width:150px\" type=\"button\">100% Brightness</button></a>");
  client.println("<br/> ");

  client.println ("<a href=\"ANIM1\"><button style=\"height:40px;width:150px\" type=\"button\">Animation 1</button></a>");
  client.println("<br/> ");
  client.println ("<a href=\"ANIM2\"><button style=\"height:40px;width:150px\" type=\"button\">Animation 2</button></a>");
  client.println("<br/> ");
  
  client.println("</td>");
  client.println("</tr>");
  client.println("</table>");

  client.println("<hr>");

  client.print("LAMPA: ");
  client.print("<br/> ");
  client.println ("<a href=\"LAMP\"><button style=\"height:40px;width:300px\" type=\"button\">WLACZ/WYLACZ</button></a>");


  delay(1);
}
