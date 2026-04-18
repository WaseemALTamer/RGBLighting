#include <WiFiUdp.h>
#include <WiFi.h>

#include <Arduino.h>
#include "config.h"
#include "network_message_manager.h"


namespace NetworkWifi{

    
    WiFiUDP udp;

    bool is_connected = false;
    int loop_cooldown_duration_ms = 3000;


    bool loop_cooldown_passed() {
        // this will let the wifi connection to try after 3 seconds
        // of not being able to connect

        static unsigned long last_event_time = 0;
        unsigned long now = millis();

        if (now - last_event_time < loop_cooldown_duration_ms) {
            return false; // ignore event
        }

        last_event_time = now;
        return true; // accept event
    }



    void init(){
        WiFi.begin(Config::network_ssid, Config::network_password);
    }

 
    void loop(){

        wl_status_t status = WiFi.status();

        if (status == WL_CONNECTED) {
            if (!is_connected){
                udp.begin(Config::network_port);
                Serial.println(WiFi.localIP());
                is_connected = true;
            }
        }else{
            is_connected = false;

            bool safe_to_reconnect =
                (status == WL_IDLE_STATUS ||
                status == WL_NO_SSID_AVAIL ||
                status == WL_DISCONNECTED ||
                status == WL_CONNECT_FAILED);

            if (safe_to_reconnect  && loop_cooldown_passed()){
                WiFi.begin(Config::network_ssid, Config::network_password);
            }
            return;
        }


        // now we can handel reading messages
        int packetSize = udp.parsePacket();
        if (packetSize > 0) {
            IPAddress senderIP = udp.remoteIP();
            int senderPort = udp.remotePort();

            uint8_t buffer[2048];
            int len = udp.read(buffer, 2048); // limit it to 2048

            MessageManager::decode_message(buffer, len);
        }

    }
}