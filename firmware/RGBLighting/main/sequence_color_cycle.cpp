
#include "sequence_system.h"
#include "lighting_manager.h"
#include "config.h"



// this file is responsible for the boot sequence
// it aims to play a  one  time sequence and this
// file should be taken  as an  example of how to
// use the SequenceSystem



// note  that this  sequence is  not a system the
// init function  will not be excuated during the 
// entry point  of this  application  the init is
// there so  it  adds the  sequence  function  to
// SequenceMnager nothing more nothing less


namespace SequenceColorCycle{


    // in the next following  steps we aim to make
    // 1 wave pattern that goes from green to blue
    // then it goes red then it goes black

    // we determain the color based on the first led 
    // when this sequence first get intiated



    
    float transition_duration = 3;
    int direction = 1;

    int offset = 0;


    TickController tick_controller;
    float current_delta = 0;


    void step_1(void* ctx){

        current_delta += tick_controller.get_elapsed();
        if (current_delta < transition_duration / 3) return;
        current_delta = 0;

        float r = 0;
        float g = 0;
        float b = 0;

        if (offset == 0) r = 1;
        if (offset == 1) g = 1;
        if (offset == 2) b = 1;

        for (int i = 0; i < LEDS_NUMBER; i++) {
            LightingManager::leds[i].transition(r, g, b, transition_duration / 3);
        }

        if (direction == 1) {
            // 0 -> 1 -> 2 -> 0
            offset = (offset + 1) % 3;
        } else {
            // 0 -> 2 -> 1 -> 0
            offset = (offset - 1 + 3) % 3;
        }
    }



    void init(){
        SequenceSystem::flush_steps(); // flush the steps before adding the new ones

        // change the damping of the leds
        for (int i = 0; i < LEDS_NUMBER; i++) {
            LightingManager::leds[i].animation.damping = 1; // set damping for the pixle so it is ease_in_out
        }


        SequenceSystem::sequence_steps[0].func = step_1;
        SequenceSystem::sequence_steps[0].cooldown = 0.015; // this will act as our tick to check our led state
    }
}