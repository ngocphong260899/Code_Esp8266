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
    pinMode(D0,OUTPUT);
    // if(WiFi.status() == WL_CONNECTED)
    // {
    //     Serial.println("Connect wifi");
    //     digitalWrite(D0,LOW);
        
    // }
    // else{
    //       digitalWrite(D0,HIGH);
    // }
    smart_config_init();
    led_btn_init();
    led_staus_start();
    mqtt_init();
    ntp_Init();
    Serial.print("Debug_print: sys_init");    
}

void button_loop()
{
    time_slice = millis();

    if (time_slice - time_handler_button_before > 50)
    {
        button_handler();
        time_handler_button_before = time_slice;
    }
}


void mqtt_loop_()
{
    time_slice = millis();

    if (time_slice - time_handler_button_before > 50)
    {
        mqtt_loop();
        time_handler_button_before = time_slice;
    }
}

void loop()
{
   
    smart_config_loop();
   
    if(WiFi.status() == WL_CONNECTED)
    {
        
        mqtt_loop();
        //button_loop();
        
    }
    button_loop();
    //get_Time_ntp();
   

}