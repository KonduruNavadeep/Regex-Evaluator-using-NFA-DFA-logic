#include "ConcatNode.h"

ConcatNode::ConcatNode(RegexNode* left, RegexNode* right) {
    this->left = left;
    this->right = right;
}

std::string ConcatNode::evaluate() {
    return left->evaluate() + right->evaluate();
}

RegexNode* ConcatNode::getLeft() {
    return left;
}

RegexNode* ConcatNode::getRight() {
    return right;
}