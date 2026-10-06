#ifndef LITERAL_NODE_H
#define LITERAL_NODE_H

#include "RegexNode.h"

class LiteralNode : public RegexNode {
private:
    char value;

public:
    LiteralNode(char value);

    std::string evaluate() override;
};

#endif