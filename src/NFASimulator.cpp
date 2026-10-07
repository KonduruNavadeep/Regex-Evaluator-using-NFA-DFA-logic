#include "NFASimulator.h"

bool NFASimulator::matches(
    NFAFragment& fragment,
    const std::string& input
) {
    std::set<NFAState*> currentStates;
    currentStates.insert(fragment.start);

    std::set<NFAState*> currentClosure;

    epsilonClosure(currentStates, currentClosure);
    currentStates = currentClosure;

    for (char symbol : input) {
        std::set<NFAState*> nextStates;

        nextStates = move(currentStates, symbol);

        std::set<NFAState*> nextClosure;

        epsilonClosure(nextStates, nextClosure);

        currentStates = nextClosure;
    }

    return currentStates.count(fragment.end) > 0;
}

void NFASimulator::epsilonClosure(
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

std::set<NFAState*> NFASimulator::move(
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