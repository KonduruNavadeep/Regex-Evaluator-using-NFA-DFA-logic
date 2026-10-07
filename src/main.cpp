#include <iostream>
#include <set>
#include "LiteralNode.h"
#include "StarNode.h"
#include "NFABuilder.h"

void printNFA(NFAState* start) {
    std::set<int> visited;
    std::vector<NFAState*> states;

    states.push_back(start);

    for (int i = 0; i < states.size(); i++) {
        NFAState* current = states[i];

        if (visited.count(current->id))
            continue;

        visited.insert(current->id);

        for (auto transition : current->transitions) {
            NFAState* destination = transition.second;

            if (!visited.count(destination->id))
                states.push_back(destination);
        }
    }

    for (NFAState* state : states) {
        for (auto transition : state->transitions) {
            if (transition.first == '\0')
                std::cout << state->id << " --EPSILON--> "
                          << transition.second->id << std::endl;
            else
                std::cout << state->id << " --" << transition.first << "--> "
                          << transition.second->id << std::endl;
        }
    }
}

int main() {
    LiteralNode a('a');
    StarNode star(&a);

    NFABuilder builder;
    NFAFragment fragment = builder.build(&star);

    std::cout << "Start: " << fragment.start->id << std::endl;
    std::cout << "End: " << fragment.end->id << std::endl;

    printNFA(fragment.start);

    return 0;
}