#pragma once

#include <Arduino.h>

namespace SequenceRainbow
{
    // expose the init function so anybody can
    // excuate it and add the schedule it 


    extern float transition_speed;

    void init();
}