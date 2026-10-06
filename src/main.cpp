#include <iostream>
#include "LiteralNode.h"
#include "UnionNode.h"

int main() {
    LiteralNode* a = new LiteralNode('a');
    LiteralNode* b = new LiteralNode('b');

    UnionNode node(a, b);

    std::cout << node.evaluate() << std::endl;

    delete a;
    delete b;

    return 0;
}