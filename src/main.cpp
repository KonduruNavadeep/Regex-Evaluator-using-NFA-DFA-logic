#include <iostream>
#include "RegexParser.h"
#include "NFABuilder.h"
#include "NFASimulator.h"

int main() {
    RegexParser parser("(a|b)*abb");
    RegexNode* root = parser.parse();

    NFABuilder builder;
    NFAFragment fragment = builder.build(root);

    NFASimulator simulator;

    std::cout << "abb: " << simulator.matches(fragment, "abb") << std::endl;
    std::cout << "aabb: " << simulator.matches(fragment, "aabb") << std::endl;
    std::cout << "ababb: " << simulator.matches(fragment, "ababb") << std::endl;
    std::cout << "abababb: " << simulator.matches(fragment, "abababb") << std::endl;
    std::cout << "ab: " << simulator.matches(fragment, "ab") << std::endl;
    std::cout << "abc: " << simulator.matches(fragment, "abc") << std::endl;

    return 0;
}