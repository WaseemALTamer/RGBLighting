#include <Arduino.h>
#include "config.h"
#include "lighting_manager.h"
#include "led_controller.h"
#include "sequence_manager.h"

#include "sequence_rainbow.h"
#include "sequence_breathing.h"
#include "sequence_wave.h"



// this file is responsible for decoding the message and excuating
// what the message wants happening or anything along those lines





uint64_t readUInt64BE(const uint8_t* data, int& index) {
    uint64_t value =
        ((uint64_t)data[index] << 56) |
        ((uint64_t)data[index + 1] << 48) |
        ((uint64_t)data[index + 2] << 40) |
        ((uint64_t)data[index + 3] << 32) |
        ((uint64_t)data[index + 4] << 24) |
        ((uint64_t)data[index + 5] << 16) |
        ((uint64_t)data[index + 6] << 8) |
        ((uint64_t)data[index + 7]);

    return value;
}


double readDoubleBE(const uint8_t* data, int& index) {
    uint64_t raw = readUInt64BE(data, index);
    double value;
    memcpy(&value, &raw, sizeof(double));
    return value;
}


// the message has two stages to be proccessed, first stage
// which every meessage contain those headers then you have
// second stage which is  either the information or command
// route and  then  you  have  a thrid  stage  which is the
// functionality of the message all the stages are inside a
// a namespace of there own 

namespace MessageManager{


    namespace Messages {


        namespace Commands {
            const uint8_t setting = 1;


            void decode_setting_command(const uint8_t* data, int len){
                if (len < 9) {
                    // setting message too small
                    return;
                }

                int index = 0;
                uint8_t brightness = data[index]; // one byte
                index += 1;
                double transition_speed = readDoubleBE(data, index); // 8 bytes

                // this is where the message ends we excuate the command now
                
                Config::brightness =  brightness/ 255.0f; // normlise it because we get it as bytes from 
                                                          // the message command message

                
                Config::transition_speed = transition_speed;

                LightingManager::pack_all_leds(); // update the led values on the go and 
                                                  // schedule the update on the leds                                                  
                
            }



            const uint8_t rgb_stream = 2;

            void decode_rgb_stream_command(const uint8_t* data, int len) {
                if (len < 8) {
                    // not even enough for leds_number
                    return;
                }

                int index = 0;

                
                uint64_t leds_number = 0;
                for (int i = 0; i < 8; i++) {
                    leds_number = (leds_number << 8) | data[index++];
                }

                
                uint64_t expected_bytes = leds_number * 3;

                if (len - index < expected_bytes) {
                    return;
                }

               
                if (leds_number == 0 || leds_number > LEDS_NUMBER) {
                    return;
                }

                // we pause the sequencer if it was running something

                SequenceManager::flush_steps();


                for (uint64_t i = 0; i < leds_number; i++) {
                    float r = data[index++] / 255.0f;
                    float g = data[index++] / 255.0f;
                    float b = data[index++] / 255.0f;

                    LightingManager::leds[i].transition(r, g, b, 0); // the 0 ensure it tranlsate instantly

                    // do not push the update  the transition with 
                    // LightingManager::pack_all_leds(); tansition
                    // function already does it for you
                }
            }


            namespace SequenceTypes{
                uint8_t rainbow = 1;
                uint8_t breathing = 2;
                uint8_t wave = 3;
            }


            const uint8_t sequence_command = 3;
            void decode_sequence_command(const uint8_t* data, int len){
                if (len < 1) {
                    // command too small return with nothing
                    return;
                }

                int index = 0;
                
                uint8_t sequence_type = data[index]; // 1 byte(x);
                index += 1;


                if (sequence_type == SequenceTypes::rainbow){
                    SequenceRainbow::init();
                }

                if (sequence_type == SequenceTypes::breathing){
                    SequenceBreathing::init();
                }

                if (sequence_type == SequenceTypes::wave){
                    SequenceWave::init();
                }



            }
        }


        const uint8_t command = 1;
        void decode_command_message(const uint8_t* data, int len) {

            if (len < 9) {
                // command too small return with nothing
                return;
            }

            int index = 0;

            uint8_t command_type = data[index]; // 1 byte(x);
            index += 1;

            uint64_t sequence = readUInt64BE(data, index); // 8 bytes
            index += 8;


            int content_size = len - index;
            const uint8_t* content = data + index;

            // detect commands types now now 
            if (command_type == Commands::setting) {
                Commands::decode_setting_command(data + index, content_size);
            }else if (command_type == Commands::rgb_stream) {
                Commands::decode_rgb_stream_command(data + index, content_size);
            }else if(command_type == Commands::sequence_command){
                Commands::decode_sequence_command(data + index, content_size);
            }


        }


        const uint8_t information = 2;
        void decode_information_message(uint8_t* data, int len){

        }
    }







    void decode_message(uint8_t* data, int len){
        if (len < 72) {
            // packet is too small to mean anything
            return;
        }

        int index = 0;
        uint8_t message_type = data[index]; // 1 byte
        index += 1;

        uint8_t mac[6];
        memcpy(mac, data + index, 6); // 6 bytes
        index += 6;

        char device_name[65]; // 64 bytes
        memcpy(device_name, data + index, 64);
        device_name[64] = '\0';
        index += 64;

        uint8_t encrypted = data[index]; // one byte
        index += 1;


        int content_size = len - index;

        // detect message types now
        if (message_type == Messages::command) {
            Messages::decode_command_message(data + index, content_size);
        }
        else if (message_type == Messages::information) {
            Messages::decode_information_message(data + index, content_size);
        }
        

    }





}