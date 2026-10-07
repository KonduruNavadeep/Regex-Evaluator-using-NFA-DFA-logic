#include "RegexParser.h"
#include "LiteralNode.h"
#include "ConcatNode.h"
#include "UnionNode.h"
#include "StarNode.h"

RegexParser::RegexParser(const std::string& regex) {
    this->regex = regex;
    pos = 0;
}

RegexNode* RegexParser::parse() {
    return parseExpression();
}

RegexNode* RegexParser::parseExpression() {
    RegexNode* node = parseTerm();

    while (pos < regex.length() && regex[pos] == '|') {
        pos++;
        RegexNode* right = parseTerm();
        node = new UnionNode(node, right);
    }

    return node;
}

RegexNode* RegexParser::parseTerm() {
    RegexNode* node = parseFactor();

    while (pos < regex.length() && regex[pos] != '|' && regex[pos] != ')') {
        RegexNode* right = parseFactor();
        node = new ConcatNode(node, right);
    }

    return node;
}

RegexNode* RegexParser::parseFactor() {
    RegexNode* node = parsePrimary();

    while (pos < regex.length() && regex[pos] == '*') {
        pos++;
        node = new StarNode(node);
    }

    return node;
}

RegexNode* RegexParser::parsePrimary() {
    if (regex[pos] == '(') {
        pos++;

        RegexNode* node = parseExpression();

        if (pos < regex.length() && regex[pos] == ')') {
            pos++;
        }

        return node;
    }

    RegexNode* node = new LiteralNode(regex[pos]);
    pos++;

    return node;
}