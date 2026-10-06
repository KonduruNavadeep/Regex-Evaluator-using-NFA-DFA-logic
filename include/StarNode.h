#ifndef STAR_NODE_H
#define STAR_NODE_H

#include "RegexNode.h"

class StarNode : public RegexNode {
private:
    RegexNode* child;

public:
    StarNode(RegexNode* child);

    std::string evaluate() override;
};

#endif