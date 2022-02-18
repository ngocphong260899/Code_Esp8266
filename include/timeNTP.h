#include "NTPClient.h"
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

void ntp_Init();
void get_Time_ntp();
void get_Alarm(JsonObject &data);
void get_Alarm_state();
void get_time_eeprom();



