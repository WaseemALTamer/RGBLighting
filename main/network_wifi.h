#pragma once

#include <WiFiUdp.h>
#include <WiFi.h>


namespace NetworkWifi
{
    // expose the init function so anybody can
    // excuate it and add the schedule it 
    void init();
    void loop();
}