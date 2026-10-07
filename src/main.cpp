#include <iostream>
#include "LiteralNode.h"
#include "UnionNode.h"
#include "NFABuilder.h"

void printTransition(NFAState* state) {
    for (auto transition : state->transitions) {
        if (transition.first == '\0')
            std::cout << state->id << " --EPSILON--> "
                      << transition.second->id << std::endl;
        else
            std::cout << state->id << " --"
                      << transition.first << "--> "
                      << transition.second->id << std::endl;
    }
}

int main() {
    LiteralNode a('a');
    LiteralNode b('b');

    UnionNode unionNode(&a, &b);

    NFABuilder builder;

    NFAFragment fragment = builder.build(&unionNode);

    std::cout << "Start: " << fragment.start->id << std::endl;
    std::cout << "End: " << fragment.end->id << std::endl;

    printTransition(fragment.start);

    NFAState* leftStart =
        fragment.start->transitions[0].second;

    NFAState* rightStart =
        fragment.start->transitions[1].second;

    printTransition(leftStart);
    printTransition(leftStart->transitions[0].second);

    printTransition(rightStart);
    printTransition(rightStart->transitions[0].second);

    return 0;
}