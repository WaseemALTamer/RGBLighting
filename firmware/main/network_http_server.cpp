#include <WiFi.h>
#include <LittleFS.h>
#include <WebServer.h>



#include "config.h"
#include "lighting_manager.h"
#include "led_controller.h"
#include "sequence_manager.h"

#include "sequence_rainbow.h"
#include "sequence_breathing.h"
#include "sequence_wave.h"
#include "network_wifi.h"




namespace HttpServer{

    WebServer server(80);


    void handle_root() {
        File file = LittleFS.open("/index.html", "r");
        server.streamFile(file, "text/html");
        file.close();
    }


    void handel_leds(){

        float transition_duration = 0;

        if (server.hasArg("transition_duration")) {
            String speedStr = server.arg("transition_duration");
            transition_duration = speedStr.toFloat();
        }

        if (server.hasArg("red") && 
            server.hasArg("green") && 
            server.hasArg("blue")) 
        {
            float red = server.arg("red").toInt();
            float green = server.arg("green").toInt();
            float blue = server.arg("blue").toInt();

            // convert from ints to float
            float r = red / 255.0f;
            float g = green / 255.0f;
            float b = blue / 255.0f;


            SequenceManager::flush_steps();

            for (uint64_t i = 0; i < LEDS_NUMBER; i++) {

                

                LightingManager::leds[i].transition(r, 
                                                    g, 
                                                    b, 
                                                    transition_duration);


            }

            server.send(200, "text/plain", "1");

        }

    }


    void handel_setting(){


        if (server.hasArg("transition_speed")) {
            String speedStr = server.arg("transition_speed");
            float transition_speed = speedStr.toFloat();
            Config::transition_speed = transition_speed;
        }


        if (server.hasArg("brightness")) {
            String brightnessStr = server.arg("brightness");
            float brightness = brightnessStr.toFloat();
            LightingManager::set_brightness(brightness);
        }

        server.send(200, "text/plain", "1");

    }



    void init() {
        LittleFS.begin();

        server.on("/", handle_root);
        server.on("/api/all_leds", handel_leds);
        server.on("/api/setting", handel_setting);
        server.begin();
    }


    void loop() {
        server.handleClient();
    }


}

