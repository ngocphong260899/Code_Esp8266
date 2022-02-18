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

typedef struct
{
    int hour;
    int minute;
    int status;
} alarm1;

typedef struct
{
    int hour;
    int minute;
    int status;
} alarm2;

alarm time_alarm;
alarm1 time_alarm1;
alarm2 time_alarm2;

void ntp_Init()
{
    timeClient.begin();
    timeClient.setTimeOffset(7 * 60 * 60);
}

// void get_Time_ntp()
// {
//     char time[100];
//     timeClient.update();
//     int hour = timeClient.getHours();
//     int minute = timeClient.getMinutes();

//     //delay(1000);
// }

void get_Alarm(JsonObject &data)
{
    char msg[100];
    int pos = data[key_json_pos];
    int hour = data[key_json_hour];
    int minute = data[key_json_minute];
    int status = data[key_status];

    switch (pos)
    {
    case 1:
    {
        Serial.println(hour);
        Serial.println(minute);
        Serial.println(status);
        time_alarm.hour = hour;
        time_alarm.minute = minute;
        time_alarm.status = status;
        EEPROM.put(0, time_alarm);
        EEPROM.commit();
        EEPROM.end();
        Serial.println("Save data alarm 1 ch");
    }
    break;
    case 2:
    {
        Serial.println(hour);
        Serial.println(minute);
        Serial.println(status);
        time_alarm1.hour = hour;
        time_alarm1.minute = minute;
        time_alarm1.status = status;
        EEPROM.put(14, time_alarm1);
        EEPROM.commit();
        EEPROM.end();
        Serial.println("Save data alarm 2 ch");
    }
    break;
    case 3:
    {
        Serial.println(hour);
        Serial.println(minute);
        Serial.println(status);
        time_alarm2.hour = hour;
        time_alarm2.minute = minute;
        time_alarm2.status = status;
        EEPROM.put(28, time_alarm2);
        EEPROM.commit();
        EEPROM.end();
        Serial.println("Save data alarm 3 ch");
    }
    break;
    }

    /*
        return true set alarm
    */
    sprintf(msg, "{\"sw_wifi\":%d}", 3);
    queueMsg(msg);
}



void get_alarm1()
{
    EEPROM.get(0, time_alarm);
    //timeClient.update();
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

void get_alarm2()
{
    EEPROM.get(0, time_alarm1);
    //timeClient.update();
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

    if ((time_alarm1.hour == timeClient.getHours()) &&
        (time_alarm1.minute == timeClient.getMinutes()))
    {
        control_IO(time_alarm1.status);
    }
}

void get_alarm3()
{
    EEPROM.get(0, time_alarm);
    //timeClient.update();
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

    if ((time_alarm2.hour == timeClient.getHours()) &&
        (time_alarm2.minute == timeClient.getMinutes()))
    {
        control_IO(time_alarm2.status);
    }
}

void get_time_eeprom()
{
    timeClient.update();
    get_alarm1();
    get_alarm2();
    get_alarm3();
}