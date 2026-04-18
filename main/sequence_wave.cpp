
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


namespace SequenceWave{


    // in the next following  steps we aim to make
    // 1 wave pattern that goes from green to blue
    // then it goes red then it goes black


    float r;
    float g;
    float b;
    
    float wave_width = 8.0f;


    EaseInOut animation;

    
    void on_callback(float value, void* ctx){
        // this will be called if there is an update
        // value is between 0-1

        float position = value * (LEDS_NUMBER - 1);

        for (int i = 0; i < LEDS_NUMBER; i++) {

            float distance = fabs(i - position);

            if (distance < wave_width) {

                float intensity = 1.0f - (distance / wave_width);

                LightingManager::leds[i].transition(
                    r * intensity,
                    g * intensity,
                    b * intensity,
                    0.05f // keep this small for smooth updates
                );

            } else {
                LightingManager::leds[i].transition(0, 0, 0, 0.05f);
            }
        }


    }


    void step_1(void* ctx){
        // in this step we  can  now move  from 1 - 0 - 1
        // and set up the same idea that i made in python
        // which abstract most of the logic away


        animation.update(); // simply update the animation

        if (!animation.uniform.is_running){
            animation.duration = Config::transition_speed;
            if (animation.uniform.current_value <= 0){
                animation.start_transition();
            }
            if (animation.uniform.current_value > 0){
                animation.reverse_transition();
            }

        }

        
    }


    void init(){
        SequenceManager::flush_steps(); // flush the steps before adding the new ones


        // change the damping of the leds
        for (int i = 0; i < LEDS_NUMBER; i++) {
            LightingManager::leds[i].animation.damping = 2; // set damping for the pixle so it is ease_in_out
        }

        r = LightingManager::leds[0].r;
        g = LightingManager::leds[0].g;
        b = LightingManager::leds[0].b;
        

        SequenceManager::sequence_steps[0].func = step_1;
        SequenceManager::sequence_steps[0].cooldown = 0.015; // this will act as our tick to check our led state

        // set up the animation
        animation.starting_value = 0;
        animation.ending_value = 1;
        animation.duration = Config::transition_speed;
        animation.add_callback(on_callback);
        
        // we kick start the animation by transitioning all of the leds 0, 0, 0
        for (int i = 0; i < LEDS_NUMBER; i++) {
            LightingManager::leds[i].transition(0, 0, 0, Config::transition_speed); // set damping for the pixle so it is ease_in_out
        }


        
    }
}