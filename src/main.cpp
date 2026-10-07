#include <iostream>
#include "LiteralNode.h"
#include "ConcatNode.h"
#include "NFABuilder.h"

int main() {
    LiteralNode a('a');
    LiteralNode b('b');

    ConcatNode concat(&a, &b);

    NFABuilder builder;

    NFAFragment fragment = builder.build(&concat);

    NFAState* first = fragment.start;
    NFAState* afterA = first->transitions[0].second;
    NFAState* afterB = afterA->transitions[1].second;

    std::cout << "Start: " << first->id << std::endl;
    std::cout << "End: " << fragment.end->id << std::endl;

    std::cout << "a: "
              << first->transitions[0].first
              << " -> "
              << afterA->id << std::endl;

    std::cout << "epsilon: "
              << afterA->transitions[0].first
              << " -> "
              << afterA->transitions[0].second->id << std::endl;

    std::cout << "b: "
              << afterA->transitions[0].second->transitions[0].first
              << " -> "
              << fragment.end->id << std::endl;

    return 0;
}