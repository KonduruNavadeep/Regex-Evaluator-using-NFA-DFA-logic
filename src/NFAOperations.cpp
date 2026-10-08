#include "NFAOperations.h"

void NFAOperations::epsilonClosure(
    const std::set<NFAState*>& states,
    std::set<NFAState*>& closure
) {
    for (NFAState* state : states) {
        if (closure.count(state))
            continue;

        closure.insert(state);

        for (auto transition : state->transitions) {
            if (transition.first == '\0') {
                std::set<NFAState*> nextState;
                nextState.insert(transition.second);

                epsilonClosure(nextState, closure);
            }
        }
    }
}

std::set<NFAState*> NFAOperations::move(
    const std::set<NFAState*>& states,
    char symbol
) {
    std::set<NFAState*> result;

    for (NFAState* state : states) {
        for (auto transition : state->transitions) {
            if (transition.first == symbol) {
                result.insert(transition.second);
            }
        }
    }

    return result;
}