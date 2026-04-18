#include <FastLED.h>

#include <TickController.h>
#include <TransitionUniform.h>
#include <TransitionEaseInOut.h>

#define NUM_LEDS (30 * 5)
#define DATA_PIN 6



EaseInOut anim;



CRGB leds[NUM_LEDS];

uint8_t hue = 0;


float x = 0;


uint32_t float_to_rgb(float r, float g, float b) {
    // Clamp
    if (r < 0.0f) r = 0.0f;
    if (r > 255.0f) r = 255.0f;

    if (g < 0.0f) g = 0.0f;
    if (g > 255.0f) g = 255.0f;

    if (b < 0.0f) b = 0.0f;
    if (b > 255.0f) b = 255.0f;

    uint8_t int_r = r;
    uint8_t int_g = g;
    uint8_t int_b = b;

    return ((uint32_t)int_r << 16) |
           ((uint32_t)int_g << 8)  |
           (uint32_t)int_b;
}






void onUpdate(float v) {

    leds[0] = float_to_rgb(v, 128, 0);
    FastLED.show();
    Serial.println(v);
    //Serial.println(v - x);
    
    x = v;


}


void setup() {

    Serial.begin(9600);

    FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);


    anim.starting_value = 0;
    anim.ending_value = 255;
    anim.duration = 2;

    anim.add_callback(onUpdate);

    anim.start_transition();

    
}

void loop() {
    anim.update();
    //Serial.println(anim.current_value);
}





/*
void loop() {

  CRGB color = CHSV(hue, 255, 255); // one color for all LEDs

  for (int i = 0; i < NUM_LEDS; i++) {
    //leds[i] = color;
  }

  leds[0] = color;

  FastLED.show();

  hue++;       // slowly change color
  delay(5);   // speed of transition
}

*/

