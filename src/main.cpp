#include <iostream>
#include <set>
#include <vector>
#include "RegexParser.h"
#include "NFABuilder.h"
#include "DFABuilder.h"
#include "DFASimulator.h"

void printDFA(DFAState* start) {
    std::set<int> visited;
    std::vector<DFAState*> states;

    states.push_back(start);

    for (int i = 0; i < states.size(); i++) {
        DFAState* current = states[i];

        if (visited.count(current->id))
            continue;

        visited.insert(current->id);

        for (auto transition : current->transitions) {
            if (!visited.count(transition.second->id))
                states.push_back(transition.second);
        }
    }

    for (DFAState* state : states) {
        std::cout << "DFA State " << state->id;

        if (state->isFinal)
            std::cout << " [FINAL]";

        std::cout << std::endl;

        std::cout << "NFA states: ";

        for (NFAState* nfaState : state->nfaStates)
            std::cout << nfaState->id << " ";

        std::cout << std::endl;

        for (auto transition : state->transitions) {
            std::cout << "  --" << transition.first << "--> DFA State "
                      << transition.second->id << std::endl;
        }

        std::cout << std::endl;
    }
}

int main() {
    RegexParser parser("(a|b)*abb");
    RegexNode* root = parser.parse();

    NFABuilder nfaBuilder;
    NFAFragment nfa = nfaBuilder.build(root);

    DFABuilder dfaBuilder;
    DFAState* dfa = dfaBuilder.build(nfa);

    DFASimulator simulator;

    std::cout << "abb: " << simulator.matches(dfa, "abb") << std::endl;
    std::cout << "aabb: " << simulator.matches(dfa, "aabb") << std::endl;
    std::cout << "ababb: " << simulator.matches(dfa, "ababb") << std::endl;
    std::cout << "abababb: " << simulator.matches(dfa, "abababb") << std::endl;
    std::cout << "ab: " << simulator.matches(dfa, "ab") << std::endl;
    std::cout << "abc: " << simulator.matches(dfa, "abc") << std::endl;

    return 0;
}