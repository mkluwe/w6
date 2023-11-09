#pragma once

#include <array>
#include <vector>

#include "types.h"

template < size_t N >
std::array< unsigned, 256 >
getCharCount( const std::vector< Word< N > > &words ) {
    std::array< unsigned, 256 > count{};
    for ( auto &w : words ) {
        for ( auto c : w ) {
            count[ reinterpret_cast< unsigned char & >( c ) ]++;
        }
    }
    return count;
}