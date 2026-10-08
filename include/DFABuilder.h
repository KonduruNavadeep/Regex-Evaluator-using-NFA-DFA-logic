#ifndef DFA_BUILDER_H
#define DFA_BUILDER_H

#include "DFAState.h"
#include "NFAFragment.h"
#include <vector>

class DFABuilder {
private:
    int stateCount;

public:
    DFABuilder();

    DFAState* build(NFAFragment& nfa);

private:
    bool containsFinalState(const std::set<NFAState*>& states);
};

#endif