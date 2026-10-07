#include <iostream>
#include "RegexParser.h"

int main() {
    RegexParser parser("(a|b)*");

    RegexNode* root = parser.parse();

    std::cout << root->evaluate() << std::endl;

    return 0;
}