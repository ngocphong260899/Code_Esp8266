#include "NTPClient.h"
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "mqtt.h"
#include "ArduinoJson.h"
#include "timeNTP.h"
#include <EEPROM.h>
#include "led_button.h"
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

typedef struct
{
    int hour;
    int minute;
    int status;
} alarm;

alarm time_alarm;

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
    char msg[100];
    int hour = data[key_json_hour];
    int minute = data[key_json_minute];
    int status = data[key_status];

    Serial.println(hour);
    Serial.println(minute);
    Serial.println(status);
    time_alarm.hour = hour;
    time_alarm.minute = minute;
    time_alarm.status = status;
    EEPROM.put(0, time_alarm);
    EEPROM.commit();
    EEPROM.end();
    Serial.println("Save data");
    /*
        return true set alarm
    */
    sprintf(msg, "{\"sw_wifi\":%d}", 3);
    queueMsg(msg);
}

void get_time_eeprom()
{
    EEPROM.get(0, time_alarm);
    timeClient.update();

    Serial.printf("HR: %u - %u, MIN: %u - %u\n",
                  time_alarm.hour, timeClient.getHours(),
                  time_alarm.minute, timeClient.getMinutes());

    static struct
    {
        int hr, min;
    } oldTime;

    if (timeClient.getHours() != oldTime.hr ||
        timeClient.getMinutes() != oldTime.min)
    {
        oldTime.hr = timeClient.getHours();
        oldTime.min = timeClient.getMinutes();
    }
    else
        return;

    if ((time_alarm.hour == timeClient.getHours()) &&
        (time_alarm.minute == timeClient.getMinutes()))
    {
        control_IO(time_alarm.status);
    }
}
