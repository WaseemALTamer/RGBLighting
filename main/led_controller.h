#pragma once

#include "tick_system/transition_uniform.h"
#include "tick_system/transition_ease_in_out.h"

#include "config.h"


namespace LEDController {

    typedef void (*LEDCallback)(float r, float g, float b, void* ctx);

    struct LEDCallbackEntry {
        LEDCallback func;
        void* context;
    };



    class LED {
    public:
        //constructor
        LED();

        float r = 0;
        float g = 0;
        float b = 0;


        float animation_current_r = 0;
        float animation_current_g = 0;
        float animation_current_b = 0;


        EaseInOut animation;




        void transition(float new_r,
                        float new_g,
                        float new_b,
                        float duration = -1.0f);

        void add_callback(LEDCallback function, void* context = nullptr);

    private:
        LEDCallbackEntry callbacks[LED_MAX_CALLBACKS];
        int callback_count = 0;

        // animation state
        float target_r = 0;
        float target_g = 0;
        float target_b = 0;

        float starting_r = 0;
        float starting_g = 0;
        float starting_b = 0;

        static void trigger(float value, void* ctx);
    };

}