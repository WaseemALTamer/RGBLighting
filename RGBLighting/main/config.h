#ifndef CONFIG_H
#define CONFIG_H


// constants  are keept  outside of  the LEDs they
// are also global so dont bother using the Config
// namespace when trying to access them
#define LEDS_NUMBER 150
#define LED_DATA_PIN 4
#define LED_MAX_CALLBACKS 1
#define SEQUENCE_MAX_STEPS 10




namespace Config{

    // dynamic vars are keep inside if you want
    // check the Config.cpp file  for how  they
    // are handled 

    extern char name[20];
    //extern char token[32];

    extern float transition_durtaion;
    extern float transition_speed;

    extern float brightness;

    extern int leds_number;
    extern int led_data_pin;


    void init();
    void loop();
}




#endif