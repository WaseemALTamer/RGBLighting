
#ifndef SEQUENCE_MANAGER_H
#define SEQUENCE_MANAGER_H

#include <Arduino.h>
#include "config.h"
#include "protocol.h"

namespace SequenceManager {

    extern SequenceType current_sequence;
    extern bool is_running;

    void stop_sequence();

    void start_sequence(SequenceType type);

    void apply_sequence(const SetSequence& content);

}

#endif // SEQUENCE_MANAGER_H
