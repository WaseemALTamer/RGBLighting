
#include "sequence_system.h"
#include "lighting_manager.h"
#include "config.h"


#include "tick_system/tick_controller.h"


// this file is responsible for the boot sequence
// it aims to play a  one  time sequence and this
// file should be taken  as an  example of how to
// use the SequenceSystem



// note  that this  sequence is  not a system the
// init function  will not be excuated during the 
// entry point  of this  application  the init is
// there so  it  adds the  sequence  function  to
// SequenceMnager nothing more nothing less


namespace SequenceRainbow{


    // in the next following  steps we aim to make
    // 1 wave pattern that goes from green to blue
    // then it goes red then it goes black


    int round_to_nearest_multiple_of_3(int value) {
        int remainder = value % 3;

        if (remainder == 1) {
            return value - 1;
        }

        if (remainder == 2) {
            return value + 1;
        }

        return value;
    }



    float wave_cycle_duration = 3;
    int color_section_length = 15;
    int offset = 0;

    TickController tick_controller;
    float current_delta = 0;
    
    void step_1(void* ctx){

        // ensure our number that have been given is a multiple of three
        color_section_length = round_to_nearest_multiple_of_3(color_section_length); 

        // make sure you only excaute 3 times a wave cycle
        // red -> green -> blue
        current_delta += tick_controller.get_elapsed();
        if (current_delta < wave_cycle_duration / color_section_length) return;
        current_delta = 0;


        for (int i = 0; i < (LEDS_NUMBER + color_section_length - 1) / color_section_length; i++) {
            int base = offset + (i * color_section_length);

            int led_index_red   = base % LEDS_NUMBER;
            int led_index_green = (base + color_section_length / 3) % LEDS_NUMBER;
            int led_index_blue  = (base + (color_section_length * 2) / 3) % LEDS_NUMBER;

            LightingManager::leds[led_index_red].transition(1, 0, 0, wave_cycle_duration / 3);
            LightingManager::leds[led_index_green].transition(0, 1, 0, wave_cycle_duration / 3);
            LightingManager::leds[led_index_blue].transition(0, 0, 1, wave_cycle_duration / 3);
        }

        offset = (offset + 1) % color_section_length;
    }


    void init(){
        SequenceSystem::flush_steps(); // flush the steps before adding the new ones


        // change the damping of the leds
        for (int i = 0; i < LEDS_NUMBER; i++) {
            LightingManager::leds[i].animation.damping = 1; // set damping for the pixle so it is uniform
        }
        


        SequenceSystem::sequence_steps[0].func = step_1;
        SequenceSystem::sequence_steps[0].cooldown = 0.015;
    }
}