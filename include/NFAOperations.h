#ifndef NFA_OPERATIONS_H
#define NFA_OPERATIONS_H

#include "NFAState.h"
#include <set>

class NFAOperations {
public:
    static void epsilonClosure(
        const std::set<NFAState*>& states,
        std::set<NFAState*>& closure
    );

    static std::set<NFAState*> move(
        const std::set<NFAState*>& states,
        char symbol
    );
};

#endif