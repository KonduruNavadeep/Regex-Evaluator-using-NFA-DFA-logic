#ifndef NFA_FRAGMENT_H
#define NFA_FRAGMENT_H

#include "NFAState.h"

class NFAFragment {
public:
    NFAState* start;
    NFAState* end;

    NFAFragment(NFAState* start, NFAState* end);
};

#endif