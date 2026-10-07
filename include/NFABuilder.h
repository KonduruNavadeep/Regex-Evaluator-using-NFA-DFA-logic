#ifndef NFA_BUILDER_H
#define NFA_BUILDER_H

#include "NFAFragment.h"
#include "RegexNode.h"

class NFABuilder {
private:
    int stateCount;

public:
    NFABuilder();

    NFAFragment build(RegexNode* node);

private:
    NFAFragment buildLiteral(RegexNode* node);
    NFAFragment buildConcat(RegexNode* node);
};

#endif