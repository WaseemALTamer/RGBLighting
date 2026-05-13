
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


namespace SequenceRainbow{


    // in the next following  steps we aim to make
    // 1 wave pattern that goes from green to blue
    // then it goes red then it goes black


    int color_section_length = 5; // determain the devision for each color 
    int offset = 0; // controls movement
    
    void step_1(void* ctx){
        int section_size = color_section_length;

        for (int i = 0; i < LEDS_NUMBER; i++) {
            int shifted_index = (i + offset);
            int section_index = (shifted_index / section_size) % 3;

            float r = 0, g = 0, b = 0;

            if (section_index == 0){
                g = 1;
            }
            else if (section_index == 1){
                b = 1;
            }
            else{
                r = 1;
            }

            // only update leds that that need update other wise continue
            if (LightingManager::leds[i].r == r&&
                LightingManager::leds[i].g == g &&
                LightingManager::leds[i].b == b){
                    continue;
                }
            
            
            LightingManager::leds[i].transition(r, g, b, Config::transition_speed * color_section_length);
        }


        offset++;
        if (offset >= section_size * 3){
            offset = 0;
        }
    }


    void init(){
        SequenceManager::flush_steps(); // flush the steps before adding the new ones


        // change the damping of the leds
        for (int i = 0; i < LEDS_NUMBER; i++) {
            LightingManager::leds[i].animation.damping = 1; // set damping for the pixle so it is uniform
        }
        


        SequenceManager::sequence_steps[0].func = step_1;
        SequenceManager::sequence_steps[0].cooldown = Config::transition_speed;
    }
}