// htmlServer.cpp

#include <ESP8266WiFi.h>
#include "../include/htmlServer.hpp"
#include "../include/components.hpp"

int getAvailableClient(WiFiServer& from, WiFiClient& to)
{
    to = from.available();
    if (!to) {
        return CLIENT_NOT_AVAILABLE_ERROR;
    }
    unsigned int timewate = 0;
    while (!to.available()) {
        delay(1);
        if (++timewate > 1800)
        {
        //timeout
        to.stop();
        return CLIENT_UNREACHABLE_ERROR;
        }
    }
    return 0;
}

void decodeRequestedColors(String request, int& red, int& green, int& blue)
{
    String colorHex = "";
    int i = 0;
    
    if (request.charAt(5) != '%');
    else
    {
        while (i < request.length())
        {
        if (request.charAt(i) == '%' && request.charAt(i + 1) == '2' && request.charAt(i + 2) == '3')
        {
            for (int m = i + 3; m < i + 9; m++) colorHex += request.charAt(m);
            break;
        }
        i++;
        }

        int number;
        number = (int) strtoll(&colorHex[0], NULL, 16);

        red = number >> 16;
        green = number >> 8 & 0xFF;
        blue = number & 0xFF;
    }
}

void decodeRequestedAnimations(String request, bool* animationsToPlay)
{
    if (request.indexOf("/LEDOFF") != -1)
    {
        animationsToPlay[0] = false;
        animationsToPlay[1] = false;
    }
    else if (request.indexOf("/ANIM1") != -1)
    {
        animationsToPlay[0] = true;
        animationsToPlay[1] = false;
    }
    else if (request.indexOf("/ANIM2") != -1)
    {
        animationsToPlay[0] = false;
        animationsToPlay[1] = true;
    }
}

void decodeRequestedBrightness(String request, float& brightness)
{
    if (request.indexOf("/LED50") != -1)
    {
        brightness=0.5;
    }
    else if (request.indexOf("/LED100") != -1)
    {
        brightness=1;
    }
}

void decodeRequestedLampSwitch(String request, Relay& lamp)
{
    if (request.indexOf("/LAMP") != -1)  lamp.toggle();
}

void printHTML(WiFiClient& client)
{
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

    client.flush();
}

