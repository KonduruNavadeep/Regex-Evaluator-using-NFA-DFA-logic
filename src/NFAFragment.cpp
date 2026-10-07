#include "NFAFragment.h"

NFAFragment::NFAFragment(NFAState* start, NFAState* end) {
    this->start = start;
    this->end = end;
}