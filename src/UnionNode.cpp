#include "UnionNode.h"

UnionNode::UnionNode(RegexNode* left, RegexNode* right) {
    this->left = left;
    this->right = right;
}

std::string UnionNode::evaluate() {
    return left->evaluate() + "|" + right->evaluate();
}

RegexNode* UnionNode::getLeft() {
    return left;
}

RegexNode* UnionNode::getRight() {
    return right;
}