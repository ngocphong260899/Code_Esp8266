#include "NTPClient.h"
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "mqtt.h"
#include "ArduinoJson.h"
#include "timeNTP.h"
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");


struct fake_data{
    int hour;
    int minute;
    int status;
}data;


void ntp_Init()
{
    timeClient.begin();
    timeClient.setTimeOffset(7 * 60 * 60);
}

void get_Time_ntp()
{
    char time[100];
    timeClient.update();
    int hour = timeClient.getHours();
    int minute = timeClient.getMinutes();
    

    //delay(1000);
}

void get_Alarm(JsonObject &data)
{
    int hour = data[key_json_hour];
    int minute = data[key_json_minute];
    int status = data[key_status];
    
    Serial.println(hour);
    Serial.println(minute);
    Serial.println(status);
    
}
