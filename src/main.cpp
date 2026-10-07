#include <iostream>
#include "NFAState.h"
#include "NFAFragment.h"

int main() {
    NFAState* start = new NFAState(0);
    NFAState* end = new NFAState(1, true);

    start->addTransition('a', end);

    NFAFragment fragment(start, end);

    std::cout << "Start: " << fragment.start->id << std::endl;
    std::cout << "End: " << fragment.end->id << std::endl;
    std::cout << "Transition: "
              << fragment.start->transitions[0].first
              << " -> "
              << fragment.start->transitions[0].second->id
              << std::endl;

    delete start;
    delete end;

    return 0;
}