#include <iostream>
#include <string>
#include "RegexParser.h"
#include "NFABuilder.h"
#include "DFABuilder.h"
#include "DFASimulator.h"

int main() {
    std::string regex;
    std::string input;

    std::cout << "Enter Regular Expression: ";
    std::cin >> regex;

    std::cout << "Enter String: ";
    std::cin >> input;

    RegexParser parser(regex);
    RegexNode* root = parser.parse();

    NFABuilder nfaBuilder;
    NFAFragment nfa = nfaBuilder.build(root);

    DFABuilder dfaBuilder;
    DFAState* dfa = dfaBuilder.build(nfa);

    DFASimulator simulator;

    bool result = simulator.matches(dfa, input);

    if (result)
        std::cout << "Result: ACCEPT" << std::endl;
    else
        std::cout << "Result: REJECT" << std::endl;

    return 0;
}