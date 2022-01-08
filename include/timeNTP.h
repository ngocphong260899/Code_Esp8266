#include "NTPClient.h"
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);



void timeClient_init()
{
    timeClient.begin();
}

