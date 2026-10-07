#ifndef REGEX_PARSER_H
#define REGEX_PARSER_H

#include <string>
#include "RegexNode.h"

class RegexParser {
private:
    std::string regex;
    int pos;

public:
    RegexParser(const std::string& regex);

    RegexNode* parse();

private:
    RegexNode* parseExpression();
    RegexNode* parseTerm();
    RegexNode* parseFactor();
    RegexNode* parsePrimary();
};

#endif