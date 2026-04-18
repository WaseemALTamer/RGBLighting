#include "tick_system/transition_ease_in_out.h"
#include "config.h"
#include "led_controller.h"



namespace LEDController{




    LED::LED() {
        animation.add_callback(trigger, this);
    }




    void LED::transition(float new_r, 
                    float new_g, 
                    float new_b,
                    float duration){

        // if you dont want animation set the duration to 0 if
        // want it to be speed based then set it to below zero
        // other wise provide the  duration your self you will
        // not be able to cahnge the color  of the  led unless
        // you go through here 
            
        r = new_r;
        g = new_g;
        b = new_b;

        // this detects if the color was 
        // set the starting value
        starting_r = animation_current_r;
        starting_g = animation_current_g;
        starting_b = animation_current_b;

        // set the target to the change
        target_r = new_r;
        target_g = new_g;
        target_b = new_b;

        // calculate max distance
        float dr = fabsf(target_r - starting_r);
        float dg = fabsf(target_g - starting_g);
        float db = fabsf(target_b - starting_b);

        float max_distance = dr;

        if (dg > max_distance) max_distance = dg;
        if (db > max_distance) max_distance = db;


        if (duration == 0){
            animation_current_r = new_r;
            animation_current_g = new_g;
            animation_current_b = new_b;
            for (int i = 0; i < callback_count; i++) {
                if (callbacks[i].func) {
                    callbacks[i].func(new_r,
                                        new_g,
                                        new_b,
                                        callbacks[i].context);
                }
            }
            
            return;
        }

        if (duration < 0){
            duration = Config::transition_speed;
        }


        animation.duration = duration;

        animation.stop_transition();
        animation.reset_transition();

        animation.start_transition();
    }


    void LED::add_callback(LEDCallback function, void* context) {
        if (callback_count < LED_MAX_CALLBACKS) {
            callbacks[callback_count++] = {function, context};
        }
    }


    void LED::trigger(float value, void* ctx) {
        LED* self = (LED*)ctx;
        if (!self) return;

        self->animation_current_r = self->starting_r + (value * (self->target_r - self->starting_r));
        self->animation_current_g = self->starting_g + (value * (self->target_g - self->starting_g));
        self->animation_current_b = self->starting_b + (value * (self->target_b - self->starting_b));

        for (int i = 0; i < self->callback_count; i++) {
            if (self->callbacks[i].func) {
                self->callbacks[i].func(self->animation_current_r,
                                        self->animation_current_g,
                                        self->animation_current_b,
                                        self->callbacks[i].context);
            }
        }
    }

    
}


