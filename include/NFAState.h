#ifndef NFA_STATE_H
#define NFA_STATE_H

#include <vector>
#include <utility>

class NFAState {
public:
    int id;
    bool isFinal;

    std::vector<std::pair<char, NFAState*>> transitions;

    NFAState(int id, bool isFinal = false);

    void addTransition(char symbol, NFAState* destination);
};

#endif