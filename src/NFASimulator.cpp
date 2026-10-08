#include "NFASimulator.h"
#include "NFAOperations.h"

bool NFASimulator::matches(
    NFAFragment& fragment,
    const std::string& input
) {
    std::set<NFAState*> currentStates;
    currentStates.insert(fragment.start);

    std::set<NFAState*> currentClosure;

    NFAOperations::epsilonClosure(
        currentStates,
        currentClosure
    );

    currentStates = currentClosure;

    for (char symbol : input) {
        std::set<NFAState*> nextStates;

        nextStates = NFAOperations::move(
            currentStates,
            symbol
        );

        std::set<NFAState*> nextClosure;

        NFAOperations::epsilonClosure(
            nextStates,
            nextClosure
        );

        currentStates = nextClosure;
    }

    return currentStates.count(fragment.end) > 0;
}