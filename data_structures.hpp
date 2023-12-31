#ifndef CUTILE_DATA_STRUCTURES_HPP
#define CUTILE_DATA_STRUCTURES_HPP

#include "./cutile.h"

#ifdef CUTILE_CPP
    template <typename T>
    struct search_result
    {
        b8 found;
        T  value;
    };
#endif

#endif // !CUTILE_DATA_STRUCTURES_HPP