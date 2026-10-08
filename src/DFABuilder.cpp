#include "DFABuilder.h"
#include "NFAOperations.h"

DFABuilder::DFABuilder() {
    stateCount = 0;
}

DFAState* DFABuilder::build(NFAFragment& nfa) {
    std::set<NFAState*> startStates;
    startStates.insert(nfa.start);

    std::set<NFAState*> startClosure;

    NFAOperations::epsilonClosure(
        startStates,
        startClosure
    );

    DFAState* startDFAState = new DFAState(
        stateCount++,
        startClosure,
        containsFinalState(startClosure)
    );

    std::set<char> alphabet;
    std::set<NFAState*> visited;
    std::vector<NFAState*> states;

    states.push_back(nfa.start);

    for (int i = 0; i < states.size(); i++) {
        NFAState* current = states[i];

        if (visited.count(current))
            continue;

        visited.insert(current);

        for (auto transition : current->transitions) {
            if (transition.first != '\0')
                alphabet.insert(transition.first);

            if (!visited.count(transition.second))
                states.push_back(transition.second);
        }
    }

        std::vector<DFAState*> dfaStates;
    dfaStates.push_back(startDFAState);

    for (int i = 0; i < dfaStates.size(); i++) {
        DFAState* current = dfaStates[i];

        for (char symbol : alphabet) {
            std::set<NFAState*> movedStates;

            movedStates = NFAOperations::move(
                current->nfaStates,
                symbol
            );

            if (movedStates.empty())
                continue;

            std::set<NFAState*> nextStates;

            NFAOperations::epsilonClosure(
                movedStates,
                nextStates
            );

            DFAState* nextDFAState = findState(
                dfaStates,
                nextStates
            );

            if (nextDFAState == nullptr) {
                nextDFAState = new DFAState(
                    stateCount++,
                    nextStates,
                    containsFinalState(nextStates)
                );

                dfaStates.push_back(nextDFAState);
            }
            current->transitions[symbol] = nextDFAState;
        }
    }

    return startDFAState;
}

bool DFABuilder::containsFinalState(
    const std::set<NFAState*>& states
) {
    for (NFAState* state : states) {
        if (state->isFinal)
            return true;
    }

    return false;
}

DFAState* DFABuilder::findState(
    const std::vector<DFAState*>& states,
    const std::set<NFAState*>& nfaStates
) {
    for (DFAState* state : states) {
        if (state->nfaStates == nfaStates)
            return state;
    }

    return nullptr;
}