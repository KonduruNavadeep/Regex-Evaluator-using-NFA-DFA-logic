#include "StarNode.h"

StarNode::StarNode(RegexNode* child) {
    this->child = child;
}

std::string StarNode::evaluate() {
    return "(" + child->evaluate() + ")*";
}