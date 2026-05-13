
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


namespace SequenceBreathing{


    // in the next following  steps we aim to make
    // 1 wave pattern that goes from green to blue
    // then it goes red then it goes black

    // we determain the color based on the first led 
    // when this sequence first get intiated
    float starting_r;
    float starting_g;
    float starting_b;


    float ending_r;
    float ending_g;
    float ending_b;


    bool is_moving_forword = false;
    void step_1(void* ctx){


        // incase the animation was stuck
        if (!LightingManager::leds[0].animation.uniform.is_running){
            for (int i = 0; i < LEDS_NUMBER; i++) {
                if (is_moving_forword){
                    LightingManager::leds[i].transition(ending_r, ending_g, ending_b, Config::transition_speed);
                }else{
                    LightingManager::leds[i].transition(starting_r, starting_g, starting_b, Config::transition_speed);
                }
            }

            is_moving_forword = !is_moving_forword;
        }
    }



    void init(){
        SequenceManager::flush_steps(); // flush the steps before adding the new ones


        // change the damping of the leds
        for (int i = 0; i < LEDS_NUMBER; i++) {
            LightingManager::leds[i].animation.damping = 2; // set damping for the pixle so it is ease_in_out
        }

        // first led and second led are special, first led
        // color is the staring color and second led color
        // is the ending color we need to get to

        starting_r = LightingManager::leds[0].r;
        starting_g = LightingManager::leds[0].g;
        starting_b = LightingManager::leds[0].b;

        ending_r = LightingManager::leds[1].r;
        ending_g = LightingManager::leds[1].g;
        ending_b = LightingManager::leds[1].b;
        

        SequenceManager::sequence_steps[0].func = step_1;
        SequenceManager::sequence_steps[0].cooldown = 0.015; // this will act as our tick to check our led state

        // we kick start the animation by transitioning all of the leds to the starting rgb
        for (int i = 0; i < LEDS_NUMBER; i++) {
            LightingManager::leds[i].transition(starting_r, starting_g, starting_b, Config::transition_speed); // set damping for the pixle so it is ease_in_out
        }
    }
}