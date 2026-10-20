#include <Arduino.h>
#include "protocol.h"
#include "protocol_event_dispatcher.h"
#include "protocol_event_handler.h"


#include "config.h"
#include "lighting_manager.h"
#include "sequence_manager.h"





namespace ProtocalEventHandler
{
    void on_bytes_stream(BytesStream content, IPAddress senderIP, uint16_t senderPort){
        //Serial.println("on_bytes_stream");
    }

    void on_command(Command content, IPAddress senderIP, uint16_t senderPort){
        //Serial.println("on_command");
    }

    void on_discovery(Discovery content, IPAddress senderIP, uint16_t senderPort){
        //Serial.println("on_discovery");
    }

    void on_information(Information content, IPAddress senderIP, uint16_t senderPort){
        //Serial.println("on_information");
    }

    void on_message(Message content, IPAddress senderIP, uint16_t senderPort){
        //Serial.println("on_message");
    }

    void on_rgb_stream(RGBStream content, IPAddress senderIP, uint16_t senderPort) {
        if (content.content == nullptr) {
            return;
        }
        // remember we are responsible for handling the bytes stream that we sent


        const uint8_t* buffer = content.content;
        uint32_t length;
        memcpy(&length, buffer, sizeof(length));
        buffer += sizeof(length);

        constexpr uint32_t BYTES_PER_LED = 3;
        if (length % BYTES_PER_LED != 0) {
            return; // this will be invalid bytes stream
        }

        uint32_t led_count = length / BYTES_PER_LED;
        uint32_t starting_led = content.starting_led;

        if (starting_led >= LEDS_NUMBER) {
            return;
        }

        SequenceManager::flush_steps(); // flush the sequence manager to remove the effect if anything is playing
                                        // this need to be removed from this part of  the  code later on down the
                                        // line after making something like a status sequence manager

        if (led_count > LEDS_NUMBER - starting_led) {
            led_count = LEDS_NUMBER - starting_led;
        }

        for (uint32_t i = 0; i < led_count; i++) {
            uint32_t offset = i * BYTES_PER_LED;

            

            float r = buffer[offset]     / 255.0f;
            float g = buffer[offset + 1] / 255.0f;
            float b = buffer[offset + 2] / 255.0f;

            LightingManager::leds[starting_led + i].transition(
                r,
                g,
                b,
                content.transition_duration
            );
        }
    }


    void on_set_brightness(SetBrightness content, IPAddress senderIP, uint16_t senderPort){
        //Serial.println("on_set_brightness");
        LightingManager::set_brightness(
            content.value / 255.0f, 
            content.transition_duration
        );
        Serial.println(content.transition_duration);
    }

    void on_set_date_time(SetDateTime content, IPAddress senderIP, uint16_t senderPort){
        //Serial.println("on_set_date_time");
    }

    void on_set_device_name(SetDeviceName content, IPAddress senderIP, uint16_t senderPort){
        //Serial.println("on_set_device_name");
    }

    void on_set_device_status(SetDeviceStatus content, IPAddress senderIP, uint16_t senderPort){
        //Serial.println("on_set_device_status");
    }

    void on_set_sequence(SetSequence content, IPAddress senderIP, uint16_t senderPort){
        //Serial.println("on_set_sequence");
    }

    void on_set_setting(SetSetting content, IPAddress senderIP, uint16_t senderPort){
        //Serial.println("on_set_setting");
    }

    void on_wifi_connect(WifiConnect content, IPAddress senderIP, uint16_t senderPort){
        //Serial.println("on_wifi_connect");
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