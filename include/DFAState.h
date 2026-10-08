#ifndef DFA_STATE_H
#define DFA_STATE_H

#include <map>
#include <set>
#include "NFAState.h"

class DFAState {
public:
    int id;
    bool isFinal;

    std::set<NFAState*> nfaStates;
    std::map<char, DFAState*> transitions;

    DFAState(
        int id,
        const std::set<NFAState*>& nfaStates,
        bool isFinal = false
    );
};

#endif