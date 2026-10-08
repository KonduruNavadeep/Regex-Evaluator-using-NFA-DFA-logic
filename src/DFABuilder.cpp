#include "DFABuilder.h"

DFABuilder::DFABuilder() {
    stateCount = 0;
}

DFAState* DFABuilder::build(NFAFragment& nfa) {
    return nullptr;
}

bool DFABuilder::containsFinalState(
    const std::set<NFAState*>& states
) {
    return false;
}