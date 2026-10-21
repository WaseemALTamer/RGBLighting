#pragma once

#include <Arduino.h>

namespace SequenceRainbow
{
    // expose the init function so anybody can
    // excuate it and add the schedule it 


    extern float wave_cycle_duration;
    extern int color_section_length; // determain the devision for each color
    extern int direction;
    void init();
}