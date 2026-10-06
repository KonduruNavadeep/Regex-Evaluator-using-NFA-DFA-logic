#ifndef UNION_NODE_H
#define UNION_NODE_H

#include "RegexNode.h"

class UnionNode : public RegexNode {
private:
    RegexNode* left;
    RegexNode* right;

public:
    UnionNode(RegexNode* left, RegexNode* right);

    std::string evaluate() override;
};

#endif