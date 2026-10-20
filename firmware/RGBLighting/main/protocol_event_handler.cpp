#include <Arduino.h>
#include "protocol.h"
#include "protocol_event_dispatcher.h"
#include "protocol_event_handler.h"








namespace ProtocalEventHandler
{
    void on_bytes_stream(BytesStream content, IPAddress senderIP, uint16_t senderPort){
        Serial.println("on_bytes_stream");
    }

    void on_command(Command content, IPAddress senderIP, uint16_t senderPort){
        Serial.println("on_command");
    }

    void on_discovery(Discovery content, IPAddress senderIP, uint16_t senderPort){
        Serial.println("on_discovery");
    }

    void on_information(Information content, IPAddress senderIP, uint16_t senderPort){
        Serial.println("on_information");
    }

    void on_message(Message content, IPAddress senderIP, uint16_t senderPort){
        Serial.println("on_message");
    }

    void on_rgb_stream(RGBStream content, IPAddress senderIP, uint16_t senderPort){
        Serial.println("on_rgb_stream");
    }

    void on_set_brightness(SetBrightness content, IPAddress senderIP, uint16_t senderPort){
        Serial.println("on_set_brightness");
    }

    void on_set_date_time(SetDateTime content, IPAddress senderIP, uint16_t senderPort){
        Serial.println("on_set_date_time");
    }

    void on_set_device_name(SetDeviceName content, IPAddress senderIP, uint16_t senderPort){
        Serial.println("on_set_device_name");
    }

    void on_set_device_status(SetDeviceStatus content, IPAddress senderIP, uint16_t senderPort){
        Serial.println("on_set_device_status");
    }

    void on_set_sequence(SetSequence content, IPAddress senderIP, uint16_t senderPort){
        Serial.println("on_set_sequence");
    }

    void on_set_setting(SetSetting content, IPAddress senderIP, uint16_t senderPort){
        Serial.println("on_set_setting");
    }

    void on_wifi_connect(WifiConnect content, IPAddress senderIP, uint16_t senderPort){
        Serial.println("on_wifi_connect");
    }

    void init(){
        ProtocalEventDispatcher::register_bytes_stream_callback(on_bytes_stream);
        ProtocalEventDispatcher::register_command_callback(on_command);
        ProtocalEventDispatcher::register_discovery_callback(on_discovery);
        ProtocalEventDispatcher::register_information_callback(on_information);
        ProtocalEventDispatcher::register_message_callback(on_message);
        ProtocalEventDispatcher::register_r_g_b_stream_callback(on_rgb_stream);
        ProtocalEventDispatcher::register_set_brightness_callback(on_set_brightness);
        ProtocalEventDispatcher::register_set_date_time_callback(on_set_date_time);
        ProtocalEventDispatcher::register_set_device_name_callback(on_set_device_name);
        ProtocalEventDispatcher::register_set_device_status_callback(on_set_device_status);
        ProtocalEventDispatcher::register_set_sequence_callback(on_set_sequence);
        ProtocalEventDispatcher::register_set_setting_callback(on_set_setting);
        ProtocalEventDispatcher::register_wifi_connect_callback(on_wifi_connect);
    }

    void loop(){

    }
}