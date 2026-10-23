#include <WiFi.h>
#include <LittleFS.h>
#include <WebServer.h>
#include <WebSocketsServer.h>


#include "config.h"
#include "lighting_manager.h"
#include "led_controller.h"
#include "sequence_system.h"

#include "sequence_rainbow.h"
#include "sequence_breathing.h"
#include "sequence_wave.h"
#include "network_wifi.h"
#include "protocol_event_dispatcher.h"



namespace HttpServer{

    WebServer server(80);
    WebSocketsServer ws_server(81);


    void on_ws_event(
        uint8_t client_num,
        WStype_t type,
        uint8_t* payload,
        size_t length
    ) {
        switch (type) {
            case WStype_CONNECTED:
                //Serial.printf("Client %u connected\n", client_num);
                break;

            case WStype_DISCONNECTED:
                //Serial.printf("Client %u disconnected\n", client_num);
                break;

            case WStype_TEXT:
                //Serial.printf("Received: %.*s\n", (int)length, (char*)payload);
                break;

            case WStype_BIN:
                //Serial.printf("Received %u binary bytes\n", (unsigned)length);
                ProtocalEventDispatcher::handle_message(
                    payload,
                    length,
                    ws_server.remoteIP(client_num), // if we send him a message it is most likely will be over udp
                    Config::network_port
                );
                break;

            default:
                break;
        }
    }


    void handle_root() {
        File file = LittleFS.open("/index.html", "r");
        server.streamFile(file, "text/html");
        file.close();
    }


    String get_content_type(const String& path) {
        if (path.endsWith(".html")) return "text/html";
        if (path.endsWith(".css"))  return "text/css";
        if (path.endsWith(".js"))   return "application/javascript";
        if (path.endsWith(".json")) return "application/json";
        if (path.endsWith(".png"))  return "image/png";
        if (path.endsWith(".jpg") || path.endsWith(".jpeg")) return "image/jpeg";
        if (path.endsWith(".gif"))  return "image/gif";
        if (path.endsWith(".svg"))  return "image/svg+xml";
        if (path.endsWith(".ico"))  return "image/x-icon";
        if (path.endsWith(".woff2")) return "font/woff2";
        if (path.endsWith(".txt"))  return "text/plain";

        return "application/octet-stream";
    }


    void handle_static_file() {
        String path = server.uri();
        if (path == "/") {
            path = "/index.html";
        }

        if (!LittleFS.exists(path)) {
            server.send(404, "text/plain", "404: File not found");
            return;
        }

        File file = LittleFS.open(path, "r");

        if (!file || file.isDirectory()) {
            server.send(404, "text/plain", "404: File not found");
            return;
        }

        server.streamFile(file, get_content_type(path));
        file.close();
    }



    /*
        the next two functions are outdated, they need to be removed after you
        implement the websocket messaging system
    */

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


            SequenceSystem::flush_steps();

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
            LightingManager::set_brightness(brightness, Config::transition_speed);
        }

        server.send(200, "text/plain", "1");
    }



    void init() {
        LittleFS.begin();


        server.onNotFound(handle_static_file);


        server.on("/api/all_leds", handel_leds);
        server.on("/api/setting", handel_setting);
        server.begin();


        ws_server.begin();
        ws_server.onEvent(on_ws_event);
    }


    void loop() {
        server.handleClient();
        ws_server.loop();
    }


}

