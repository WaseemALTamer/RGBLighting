
#include "sequence_manager.h"
#include "lighting_manager.h"
#include "config.h"



// this file is responsible for the boot sequence
// it aims to play a  one  time sequence and this
// file should be taken  as an  example of how to
// use the SequenceManager



// note  that this  sequence is  not a system the
// init function  will not be excuated during the 
// entry point  of this  application  the init is
// there so  it  adds the  sequence  function  to
// SequenceMnager nothing more nothing less


namespace SequenceBoot{


    // in the next following  steps we aim to make
    // 1 wave pattern that goes from green to blue
    // then it goes red then it goes black 

    int current_led_index_step_1 = 0;
    void step_1(void* ctx){
        // this step should be added as the
        // first step of index 0

        if (current_led_index_step_1 >= LEDS_NUMBER){
            return;
        }

        if (current_led_index_step_1 < 0){
            current_led_index_step_1 ++;
            return;
        }

        LightingManager::leds[current_led_index_step_1].transition(0, 1, 0, 0.5);

        current_led_index_step_1 ++;
    }

    int current_led_index_step_2 = -5;
    void step_2(void* ctx){
        // this step should be added as the
        // second step of index 1
        if (current_led_index_step_2 >= LEDS_NUMBER){
            return;
        }

        if (current_led_index_step_2 < 0){
            current_led_index_step_2 ++;
            return;
        }

        LightingManager::leds[current_led_index_step_2].transition(0, 0, 1, 0.5);

        current_led_index_step_2 ++;
    }


    int current_led_index_step_3 = -10;
    void step_3(void* ctx){
        // this step should be added as the
        // thrid step of index 2
        if (current_led_index_step_3 >= LEDS_NUMBER){
            return;
        }

        if (current_led_index_step_3 < 0){
            current_led_index_step_3 ++;
            return;
        }

        LightingManager::leds[current_led_index_step_3].transition(1, 0, 0, 0.5);

        current_led_index_step_3 ++;
    }


    int current_led_index_step_4 = -15;
    void step_4(void* ctx){
        // this step should be added as the
        // thrid step of index 2
        if (current_led_index_step_4 >= LEDS_NUMBER){
            // since step 4 is the final step flush the steps
            SequenceManager::flush_steps();
            return;
        }

        if (current_led_index_step_4 < 0){
            current_led_index_step_4 ++;
            return;
        }

        LightingManager::leds[current_led_index_step_4].transition(0, 0, 0, 0.5);

        current_led_index_step_4 ++;
    }





    void init(){

        SequenceManager::flush_steps(); // flush the steps before adding the new ones

        // each step takes 0.025, each step is 5 leds behind
        // and there is 4  steps means  each led can go from
        // one color to another and have 0.025 * 4 * 5 = 0.5
        // seconds to transition from one color to another

        SequenceManager::sequence_steps[0].func = step_1;
        SequenceManager::sequence_steps[0].cooldown = 0.025;


        SequenceManager::sequence_steps[1].func = step_2;
        SequenceManager::sequence_steps[1].cooldown = 0.025;


        SequenceManager::sequence_steps[2].func = step_3;
        SequenceManager::sequence_steps[2].cooldown = 0.025;


        SequenceManager::sequence_steps[3].func = step_4;
        SequenceManager::sequence_steps[3].cooldown = 0.025;
    }
}