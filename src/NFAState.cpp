#include "NFAState.h"

NFAState::NFAState(int id, bool isFinal) {
    this->id = id;
    this->isFinal = isFinal;
}

void NFAState::addTransition(char symbol, NFAState* destination) {
    transitions.push_back({symbol, destination});
}