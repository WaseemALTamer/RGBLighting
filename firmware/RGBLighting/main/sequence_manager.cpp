#include <Arduino.h>
#include "tick_system/tick_controller.h"
#include "config.h"
#include "lighting_manager.h"
#include "led_controller.h"
#include "sequence_system.h"

#include "protocol.h"

#include "sequence_rainbow.h"
#include "sequence_breathing.h"
#include "sequence_wave.h"

// this file will be responsible for excuating sequence of
// instructions, it will do it in  steps each step contain
// a waiting  period before  excuating the next extraction
// thisit will  aim to do  it  without  blocking  the main
// thread 





namespace SequenceManager {

    SequenceType current_sequence = SEQUENCE_TYPE_NONE;
    bool is_running = false;

    void stop_sequence() {
        if (!is_running) return;

        SequenceSystem::flush_steps();

        is_running = false;
        current_sequence = SEQUENCE_TYPE_NONE;
    }

    void start_sequence(SequenceType type) {
        if (is_running && current_sequence == type) {
            return;
        }

        stop_sequence();

        switch (type) {
            case SEQUENCE_TYPE_RAINBOW:
                SequenceRainbow::init();
                break;

            case SEQUENCE_TYPE_BREATHING:
                SequenceBreathing::init();
                break;

            case SEQUENCE_TYPE_WAVE:
                SequenceWave::init();
                break;

            default:
                return;
        }

        current_sequence = type;
        is_running = true;
    }

    void apply_sequence(const SetSequence& content) {
        switch (content.sequence) {
            case SEQUENCE_TYPE_RAINBOW:
                SequenceRainbow::wave_cycle_duration = content.speed;
                SequenceRainbow::color_section_length = content.width;
                break;

            case SEQUENCE_TYPE_BREATHING:
                SequenceBreathing::starting_r = content.color_one[2] / 255.0f;
                SequenceBreathing::starting_g = content.color_one[1] / 255.0f;
                SequenceBreathing::starting_b = content.color_one[0] / 255.0f;

                SequenceBreathing::ending_r = content.color_two[2] / 255.0f;
                SequenceBreathing::ending_g = content.color_two[1] / 255.0f;
                SequenceBreathing::ending_b = content.color_two[0] / 255.0f;


                SequenceBreathing::transition_speed = content.speed;
                break;

            case SEQUENCE_TYPE_WAVE:
                SequenceWave::r = content.color_one[2] / 255.0f;
                SequenceWave::g = content.color_one[1] / 255.0f;
                SequenceWave::b = content.color_one[0] / 255.0f;

                SequenceWave::background_r = content.color_two[2] / 255.0f;
                SequenceWave::background_g = content.color_two[1] / 255.0f;
                SequenceWave::background_b = content.color_two[0] / 255.0f;

                SequenceWave::transition_speed = content.speed;
                SequenceWave::wave_width = content.width;
                break;

            default:
                return;
        }

        // start only if the requested sequence isn't already running.
        if (!is_running || current_sequence != content.sequence) {
            start_sequence(content.sequence);
        }
    }
}