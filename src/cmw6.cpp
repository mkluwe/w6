#include <algorithm>

#include "getCharCount.h"
#include "getRanks.h"
#include "guess.h"
#include "readWords.h"
#include "usage.h"
#include "writeWords.h"

auto getScoreFn( const std::vector< Word > &words ) {
    auto count = getCharCount( words );
    auto rank = getRanks( count );
    static const auto N = std::tuple_size_v< Word >;
    return [ = ]( const Word &w ) {
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

int main( int argc, char *argv[] ) {
    if ( argc != 2 ) {
        return usage();
    }
    auto words = readWords( argv[ 1 ] );
    auto score = getScoreFn( words );
    std::sort( words.begin(), words.end(),
               [ = ]( const Word &a, const Word &b ) {
                   return score( a ) < score( b );
               } );
    guess( words );
    writeWords( argv[ 1 ], words );
}