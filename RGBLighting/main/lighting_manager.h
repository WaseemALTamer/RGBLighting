#ifndef LIGHTING_MANAGER_H
#define LIGHTING_MANAGER_H

#include <FastLED.h>
#include "config.h"
#include "led_controller.h"

namespace LightingManager {



    extern bool schedule_update;

    extern LEDController::LED leds[LEDS_NUMBER];


    void init();
    void loop();

}

#endif