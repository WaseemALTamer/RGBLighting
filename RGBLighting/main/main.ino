
#include <Arduino.h>
#include "config.h"
#include "lighting_manager.h"
#include "sequence_manager.h"

#include "sequence_boot.h"


// this is the entery point of the project there is no logic
// that runs in this file


// note the initilisation and looping through the system
// is done in order be aware if you change those

void setup() {

    Serial.begin(9600);

    // initialise the config/load the data
    // note that the Config  should be the
    // first namespace you initiate almost
    // all the other files will be relying
    // on the config file 
    Config::init();

    LightingManager::init();
    SequenceManager::init();


    SequenceBoot::init(); // add the boot sequence
}

void loop() {


    SequenceManager::loop();
    LightingManager::loop();
}





