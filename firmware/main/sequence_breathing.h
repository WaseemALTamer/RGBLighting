#pragma once

#include <Arduino.h>

namespace SequenceBreathing
{
    // expose the init function so anybody can
    // excuate it and add the schedule it


    extern float starting_r;
    extern float starting_g;
    extern float starting_b;


    extern float ending_r;
    extern float ending_g;
    extern float ending_b;

    
    void init();
}