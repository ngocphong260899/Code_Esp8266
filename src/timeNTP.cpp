#include "NTPClient.h"
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "mqtt.h"
#include "ArduinoJson.h"
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");


void ntp_Init(){
    timeClient.begin();
    timeClient.setTimeOffset(7);
}


void get_Alarm( JsonObject &data )
{
    int hour = data[key_json_hour];
    int minute = data[key_json_minute];
    int status = data[key_status];
    
}


