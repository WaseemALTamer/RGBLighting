#pragma once

#include <Arduino.h>

namespace SequenceColorCycle
{
    // expose the init function so anybody can
    // excuate it and add the schedule it


    extern float transition_duration;
    extern int direction;
    
    void init();
}