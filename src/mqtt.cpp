#include "mqtt.h"
#include "led_button.h"
#include "smartConfig.h"
#include "timeNTP.h"
WiFiClient espClient;
PubSubClient client(espClient);
typedef enum
{
    CONTROL_IO = 1,
    GET_STT_IO = 2,
    GET_ALARM = 3,
    GET_ALARM_STATE = 4

} ctr_device;

typedef enum
{
    SWITCH1 = 1,
    SWITCH2 = 2,
    SWITCH3 = 3
} position;

void mqtt_connect()
{
    if (!client.connected())
    {
        Serial.println("Dang ket noi MQTT...");
        // Connect MQTT
        if (client.connect(mqtt_client_id, mqtt_user, mqtt_password))
        {
            Serial.println("Da ket noi xong MQTT"); // Ket noi xong , hien thi
            client.subscribe(mqtt_topic_sub);
        }
        else
        {
            Serial.print("No connect: ");
            Serial.print(client.state());
            Serial.println("Doi 5 giay");
            //delay(5000);
        }
    }
}

void mqtt_loop()
{
    if (!client.connected())
    {
        mqtt_connect();
    }
    client.loop();
}

void callback(char *p_toppic, uint8_t *p_data, unsigned int length)
{
    Serial.println((char*)p_data);
    StaticJsonBuffer<1024> JSONBuffer;
    JsonObject &data = JSONBuffer.parseObject((char *)p_data);
    if (!data.success())
    {
        Serial.print("Debug_print: Json not convert");
        return;
    }
    uint8_t sw_wifi = (uint8_t)data[key_json_sw_wifi];
    uint8_t status = (uint8_t)data[key_status];
    switch (sw_wifi)
    {
    case CONTROL_IO:
    {
        Serial.println("control IO");
        control_IO(status);
    }
    break;

    case GET_STT_IO:
    {
        Serial.println("Get state");
        get_State_IO();
        get_Wifi();
    }
    break;

    case GET_ALARM:
    {
        Serial.println("Set Alarm");
        get_Alarm(data);
    }
    break;
    case GET_ALARM_STATE:
    {
        get_Alarm_state();
    }break;
    }
    
}

void mqtt_init()
{
    client.setServer(mqtt_server_ip, mqtt_port);
    client.setCallback(callback);
}

void queueMsg(char *msg)
{
    client.publish(mqtt_topic_pub, msg);
}
