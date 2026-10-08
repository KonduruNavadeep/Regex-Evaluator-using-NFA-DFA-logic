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
    if (regex.empty())
        return nullptr;

    RegexNode* node = parseExpression();

    if (node == nullptr)
        return nullptr;

    if (pos != regex.length())
        return nullptr;

    return node;
}

RegexNode* RegexParser::parseExpression() {
    RegexNode* node = parseTerm();

    if (node == nullptr)
        return nullptr;

    while (pos < regex.length() && regex[pos] == '|') {
        pos++;

        RegexNode* right = parseTerm();

        if (right == nullptr)
            return nullptr;

        node = new UnionNode(node, right);
    }

    return node;
}


RegexNode* RegexParser::parseTerm() {
    RegexNode* node = parseFactor();

    if (node == nullptr)
        return nullptr;

    while (pos < regex.length() &&
           regex[pos] != '|' &&
           regex[pos] != ')') {
        RegexNode* right = parseFactor();

        if (right == nullptr)
            return nullptr;

        node = new ConcatNode(node, right);
    }

    return node;
}


RegexNode* RegexParser::parseFactor() {
    RegexNode* node = parsePrimary();

    if (node == nullptr)
        return nullptr;

    if (pos < regex.length() && regex[pos] == '*') {
        pos++;
        node = new StarNode(node);

        if (pos < regex.length() && regex[pos] == '*')
            return nullptr;
    }

    return node;
}

RegexNode* RegexParser::parsePrimary() {
    if (pos >= regex.length())
        return nullptr;

    
    if (regex[pos] == '(') {
        pos++;

        if (pos < regex.length() && regex[pos] == ')')
            return nullptr;

        RegexNode* node = parseExpression();

        if (node == nullptr)
            return nullptr;

        if (pos >= regex.length() || regex[pos] != ')')
            return nullptr;

        pos++;

        return node;
    }

    if (regex[pos] == '*' || regex[pos] == '|')
        return nullptr;

    RegexNode* node = new LiteralNode(regex[pos]);
    pos++;

    return node;
}