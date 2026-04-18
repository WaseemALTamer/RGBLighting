#pragma once

#include <Arduino.h>

namespace SequenceWave
{
    // expose the init function so anybody can
    // excuate it and add the schedule it 
    
    
    extern float r;
    extern float g;
    extern float b;

    extern float wave_width;
    
    void init();
}