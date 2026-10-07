#ifndef NFA_SIMULATOR_H
#define NFA_SIMULATOR_H

#include "NFAFragment.h"
#include <string>
#include <set>

class NFASimulator {
public:
    bool matches(NFAFragment& fragment, const std::string& input);

private:
    void epsilonClosure(
        const std::set<NFAState*>& states,
        std::set<NFAState*>& closure
    );

    std::set<NFAState*> move(
        const std::set<NFAState*>& states,
        char symbol
    );
};

#endif