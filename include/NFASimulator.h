#ifndef NFA_SIMULATOR_H
#define NFA_SIMULATOR_H

#include "NFAFragment.h"
#include <string>

class NFASimulator {
public:
    bool matches(NFAFragment& fragment, const std::string& input);
};

#endif