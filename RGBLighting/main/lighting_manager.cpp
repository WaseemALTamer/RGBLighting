// this files is going to be the base  file that controlles the leds
// dont try to controll the leds in other methode other than through
// this file




#include <FastLED.h>
#include "config.h"
#include "led_controller.h"
#include <Arduino.h>




namespace LightingManager{



    bool schedule_update = false; 

    
    
    LEDController::LED leds[LEDS_NUMBER];
    CRGB fast_leds[LEDS_NUMBER];



    uint32_t packRGB(float r, float g, float b) {
        
        // clip the values
        if (r < 0.0f) r = 0.0f;
        if (r > 1) r = 1;

        if (g < 0.0f) g = 0.0f;
        if (g > 1) g = 1;

        if (b < 0.0f) b = 0.0f;
        if (b > 1) b = 1;


        // apply brightness
        r = r * Config::brightness;
        g = g * Config::brightness;
        b = b * Config::brightness;

        // times by 255 and convert to an int
        uint8_t int_r = (uint8_t)(r * 255.0f);
        uint8_t int_g = (uint8_t)(g * 255.0f);
        uint8_t int_b = (uint8_t)(b * 255.0f);

        return ((uint32_t)int_r << 16) |
            ((uint32_t)int_g << 8)  |
            (uint32_t)int_b;
    }


    static void on_led_callback(float r, float g, float b, void* ctx){
        CRGB* self = (CRGB*)ctx;
        if (!self) return;
        *self = packRGB(r, g, b); // apply the value now

        schedule_update = true;
    }


    void update(){
        // this function is responsible on writing on
        // the leds in real life

        FastLED.show();
        schedule_update = false;

    }

    

    void init(){
        // add the leds to be publics
        FastLED.addLeds<WS2812, LED_DATA_PIN, GRB>(fast_leds, LEDS_NUMBER);
        FastLED.setBrightness(255);

        // add the trigger function

        for (int i = 0; i < LEDS_NUMBER; i++) {
            LEDController::LED& led = leds[i];
            CRGB& fast_led = fast_leds[i];

            led.add_callback(on_led_callback, &fast_led);
        }



        //for (int i = 0; i < LEDS_NUMBER; i++) {
        //    LEDController::LED& led = leds[i];
        //    led.transition(i * 0.005, i * 0.005, 0.05, i *0.05);
        //}
    }


    void loop(){

        for (int i = 0; i < LEDS_NUMBER; i++) {
            LEDController::LED& led = leds[i];
            led.animation.update();
        }

        if (schedule_update){
            update();
        }
    }



}