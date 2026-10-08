#ifndef DFA_SIMULATOR_H
#define DFA_SIMULATOR_H

#include "DFAState.h"
#include <string>

class DFASimulator {
public:
    bool matches(DFAState* start, const std::string& input);
};

#endif