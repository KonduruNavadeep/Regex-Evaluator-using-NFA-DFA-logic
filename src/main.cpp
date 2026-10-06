#include <iostream>
#include "LiteralNode.h"
#include "ConcatNode.h"

int main() {
    LiteralNode* a = new LiteralNode('a');
    LiteralNode* b = new LiteralNode('b');

    ConcatNode node(a, b);

    std::cout << node.evaluate() << std::endl;

    delete a;
    delete b;

    return 0;
}