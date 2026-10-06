#ifndef CONCAT_NODE_H
#define CONCAT_NODE_H

#include "RegexNode.h"

class ConcatNode : public RegexNode {
private:
    RegexNode* left;
    RegexNode* right;

public:
    ConcatNode(RegexNode* left, RegexNode* right);

    std::string evaluate() override;
};

#endif