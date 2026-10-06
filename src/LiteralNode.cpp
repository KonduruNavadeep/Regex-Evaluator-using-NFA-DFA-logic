#include "LiteralNode.h"

LiteralNode::LiteralNode(char value) {
    this->value = value;
}

std::string LiteralNode::evaluate() {
    return std::string(1, value);
}