#include "NFABuilder.h"
#include "LiteralNode.h"
#include "ConcatNode.h"

NFABuilder::NFABuilder() {
    stateCount = 0;
}

NFAFragment NFABuilder::build(RegexNode* node) {
    LiteralNode* literal = dynamic_cast<LiteralNode*>(node);

    if (literal != nullptr) {
        return buildLiteral(literal);
    }

    ConcatNode* concat = dynamic_cast<ConcatNode*>(node);

    if (concat != nullptr) {
        return buildConcat(concat);
    }

    return NFAFragment(nullptr, nullptr);
}

NFAFragment NFABuilder::buildLiteral(RegexNode* node) {
    LiteralNode* literal = dynamic_cast<LiteralNode*>(node);

    char value = literal->evaluate()[0];

    NFAState* start = new NFAState(stateCount++);
    NFAState* end = new NFAState(stateCount++, true);

    start->addTransition(value, end);

    return NFAFragment(start, end);
}

NFAFragment NFABuilder::buildConcat(RegexNode* node) {
    ConcatNode* concat = dynamic_cast<ConcatNode*>(node);

    NFAFragment left = build(concat->getLeft());
    NFAFragment right = build(concat->getRight());

    left.end->isFinal = false;
    left.end->addTransition('\0', right.start);

    return NFAFragment(left.start, right.end);
}