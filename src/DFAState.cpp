#include "DFAState.h"

DFAState::DFAState(
    int id,
    const std::set<NFAState*>& nfaStates,
    bool isFinal
) {
    this->id = id;
    this->nfaStates = nfaStates;
    this->isFinal = isFinal;
}