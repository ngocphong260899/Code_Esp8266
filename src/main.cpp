#include <Arduino.h>
#include <string.h>
#include "led_button.h"
#include "mqtt.h"
#include "smartConfig.h"
#include <Ticker.h>
#include "timeNTP.h"
static uint32_t time_slice = 0;
static uint32_t time_handler_button_before = 0;
//const char *ssid = "VNPT TUAN";
//const char *password = "";

void setup()
{
    Serial.begin(115200);
    WiFi.begin();

    pinMode(D0, OUTPUT);
    // if(WiFi.status() == WL_CONNECTED)
    // {
    //     Serial.println("Connect wifi");
    //     digitalWrite(D0,LOW);

    // }
    // else{
    //       digitalWrite(D0,HIGH);
    // }
    smart_config_init();
    WiFi.reconnect();
    led_btn_init();
    led_staus_start();
    mqtt_init();
    ntp_Init();
    Serial.print("Debug_print: sys_init");
}

void button_loop()
{
    time_slice = millis();

    if (time_slice - time_handler_button_before > 20)
    {
        button_handler();
        time_handler_button_before = time_slice;
    }
}

void mqtt_loop_()
{
    time_slice = millis();

    if (time_slice - time_handler_button_before > 10)
    {
        mqtt_loop();
        time_handler_button_before = time_slice;
    }
}
void alarm_loop()
{
    static uint32_t oldMillisAlarm = 0;
    if (millis() - oldMillisAlarm > 1000)
    {
        oldMillisAlarm = time_slice;

        get_time_eeprom();
    }
}
void check_Wifi_connect()
{
    time_slice = millis();

    if (time_slice - time_handler_button_before > 10)
    {

        digitalWrite(D0, HIGH);
    }
    time_handler_button_before = time_slice;
}

void loop()
{
    smart_config_loop();

    if (WiFi.status() == WL_CONNECTED)
    {
        digitalWrite(D0, LOW);
        mqtt_loop();
        //button_loop();
        //
    }
    else if (WiFi.status() == WL_DISCONNECTED)
    {
        digitalWrite(D0, HIGH);
    }

    button_loop();
    alarm_loop();
}