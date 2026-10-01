#ifndef REGEX_NODE_H
#define REGEX_NODE_H

#include <string>

class RegexNode {
public:
    virtual ~RegexNode() = default;
    virtual std::string evaluate() = 0;
};

#endif