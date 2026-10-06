#include <iostream>
#include "LiteralNode.h"
#include "StarNode.h"

int main() {
    LiteralNode* a = new LiteralNode('a');

    StarNode node(a);

    std::cout << node.evaluate() << std::endl;

    delete a;

    return 0;
}