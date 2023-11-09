#pragma once

#include <vector>

#include "getCharCount.h"
#include "getRanks.h"

template < size_t N >
auto getScoreFn( const std::vector< Word< N > > &words ) {
    auto count = getCharCount( words );
    auto rank = getRanks( count );
    return [ = ]( const Word< N > &w ) {
        unsigned score = 0;
        for ( unsigned i = 0; i < N; ++i ) {
            score +=
                rank[ reinterpret_cast< const unsigned char & >( w[ i ] ) ];
            for ( unsigned j = i + 1; j < N; ++j ) {
                unsigned same = w[ i ] == w[ j ];
                score += same * 5;
            }
        }
        return score;
    };
}
