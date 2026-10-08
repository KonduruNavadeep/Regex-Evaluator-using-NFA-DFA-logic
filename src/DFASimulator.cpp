#include "DFASimulator.h"

bool DFASimulator::matches(
    DFAState* start,
    const std::string& input
) {
    DFAState* current = start;

    for (char symbol : input) {
        if (current->transitions.count(symbol) == 0)
            return false;

        current = current->transitions[symbol];
    }

    return current->isFinal;
}